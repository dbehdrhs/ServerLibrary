#include "stdafx.h"
#include "IocpServer.h"


IocpServer::IocpServer()
{
	Init();
}

IocpServer::~IocpServer()
{
}

void IocpServer::Init()
{
	iocp_ = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, workerThreadCount_);
}

void IocpServer::Release()
{
}

bool IocpServer::CreateListenSocket()
{
	listenSocket_ = socket(AF_INET, SOCK_STREAM, 0);

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
			continue;
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
			break;
		case IO_RECV:
			session->OnRecv();
			break;
		default:
			SessionManager::Instance().CloseSession(session);
			break;
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