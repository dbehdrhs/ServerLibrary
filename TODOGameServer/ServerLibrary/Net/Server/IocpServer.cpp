#include "stdafx.h"
#include "IocpServer.h"


IocpServer::IocpServer()
{
	Init();
}

IocpServer::~IocpServer()
{
	Release();
}

void IocpServer::Init()
{
	if (!CreateListenSocket())
		return;

	iocp_ = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, workerThreadCount_);

	run();
}

void IocpServer::Release()
{
	CloseHandle(iocp_);
}

bool IocpServer::CreateListenSocket()
{
	listenSocket_ = WSASocket(AF_INET, SOCK_STREAM, NULL, NULL, 0, WSA_FLAG_OVERLAPPED);

	SOCKADDR_IN serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port_);
	inet_pton(AF_INET, ip_, &(serverAddr.sin_addr));

	int reUseAddr = 1;
	setsockopt(listenSocket_, SOL_SOCKET, SO_REUSEADDR, (char*)&reUseAddr, sizeof(reUseAddr));

	int retVal = ::bind(listenSocket_, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	if (retVal == SOCKET_ERROR)
	{
		cout << "[ERROR] bind failed" << endl;
		return false;
	}

	retVal = listen(listenSocket_, SOMAXCONN);
	if (retVal == SOCKET_ERROR)
	{
		cout << "[ERROR] listen failed" << endl;
		return false;
	}

	return true;
}

void IocpServer::run()
{
	if (MAX_IOCP_THREAD_COUNT < workerThreadCount_)
	{
		// workerThread limit over;
	}

	acceptThread_ = MAKE_THREAD(IocpServer, AcceptThread);

	for (int i = 0; i < workerThreadCount_; i++)
	{
		workerThread_[i] = MAKE_THREAD(IocpServer, WorkerThread);
	}

	status_ = SERVER_RUN;

	// Iocp서버에서 처리할 command
	while (!g_shutDown)
	{
		// command 입력
		array<char, SIZE_64> cmdLine;
		cout << "input command : ";
		cin >> cmdLine.data();
		cout << cmdLine.data() << endl;
		//cout << "command : " << cmdLine.data() << endl;
	}
}

bool IocpServer::OnAccept(SOCKET clientSock, SOCKADDR_IN clientAddr)
{
	IocpSession* session = new IocpSession(clientSock, clientAddr);

	if (!session)
	{
		cout << "[ERROR] Accept Session is fail to create" << endl;
		SAFE_DELETE(session);
		return false;
	}
	
	if (!SessionManager::Instance().AddSession(session))
	{
		SAFE_DELETE(session);
		return false;
	}

	if (!AssociateSession(session))
	{
		SessionManager::Instance().CloseSession(session);
		return false;
	}

	session->ReadyRecv();

	return true;
}

DWORD IocpServer::AcceptThread(PVOID pParam)
{
	IocpServer* server = (IocpServer*)pParam;

	while (!g_shutDown)
	{
		SOCKADDR_IN clientAddr;
		int addrLen = sizeof(clientAddr);

		SOCKET clientSock = WSAAccept(server->ListenSocket(), (SOCKADDR*)&clientAddr, &addrLen, NULL, NULL);

		if (clientSock == SOCKET_ERROR)
		{
			// ERROR
		}

		server->OnAccept(clientSock, clientAddr);
	}

	return 0;
}

DWORD IocpServer::WorkerThread(PVOID serverPtr)
{
	IocpServer* server = (IocpServer*)serverPtr;

	DWORD transferSize;
	IocpSession* session;
	IoData* ioData;

	while (!g_shutDown)
	{
		if (!GetQueuedCompletionStatus(server->Iocp(), &transferSize, (PULONG_PTR)&session, (LPOVERLAPPED*)&ioData, INFINITE))
			continue;

		if (!session)
		{
			cout << "[ERROR] Invalid Session" << endl;
			return 0;
		}

		if (transferSize == 0)
		{
			SessionManager::Instance().CloseSession(session);
			continue;
		}

		switch (ioData->type())
		{
		case IO_SEND:
			session->OnSend();
			continue;
		case IO_RECV:
			session->OnRecv();
			continue;
		default:
			SessionManager::Instance().CloseSession(session);
			continue;
		}
	}

	return 0;
}

bool IocpServer::AssociateSession(IocpSession* session)
{
	HANDLE handle = CreateIoCompletionPort((HANDLE)session->Socket(), iocp_, (ULONG_PTR)&session, 0);
	if (!handle)
	{
		cout << "[ERROR] Socket associate failed" << endl;
		return false;
	}

	return true;
}

bool IocpServer::OnRecv()
{
	// enqueue
	return false;
}