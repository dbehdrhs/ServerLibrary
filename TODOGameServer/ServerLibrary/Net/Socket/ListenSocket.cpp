#include "stdafx.h"
#include "ListenSocket.h"


ListenSocket::ListenSocket()
{
}

ListenSocket::~ListenSocket()
{
}

void ListenSocket::CreateListenSocket(int af, int type, int protocol)
{
	if (!CreateSocket(af, type, protocol))
		return;

	if (!Bind(af))
		return;

	if (!Listen())
		return;

	array<char, SIZE_64> ip;
	inet_ntop(addr_.sin_family, &addr_, ip.data(), ip.size());
	printf("[INFO] Create Listen Socket, [IP]:%s, [port]:%d", ip.data(), addr_.sin_port);
}

BOOL ListenSocket::Bind(int af)
{
	addr_.sin_family = af;
	addr_.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_.sin_port = htons(9090);

	int retVal = ::bind(sock_, (SOCKADDR*)&addr_, sizeof(addr_));
	if (retVal == SOCKET_ERROR)
	{
		cout << "[ERROR] Bind Failed" << endl;
		return FALSE;
	}

	return TRUE;
}

BOOL ListenSocket::Listen()
{
	int retVal = listen(sock_, SOMAXCONN);

	if (retVal == SOCKET_ERROR)
	{
		cout << "[ERROR] Listen Failed" << endl;
		return FALSE;
	}

	return TRUE;
}

ClientSession* ListenSocket::Accept()
{
	ClientSession* session = new ClientSession;
	int addrLen = sizeof(session->Addr());
	SOCKET sock = session->Socket();
	
	sock = accept(sock_, (SOCKADDR*)&session->Addr(), &addrLen);
	
	SessionManager::Instance().AddSession(session);

	return session;
}

DWORD ListenSocket::AcceptThread(LPVOID serverPtr)
{
	while (!g_shutDown)
	{

	}

	return 0;
}
