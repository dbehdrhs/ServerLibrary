#include "stdafx.h"
#include "IocpSession.h"


IocpSession::IocpSession()
{
}

IocpSession::~IocpSession()
{
}

void IocpSession::OnRecv()
{
}

void IocpSession::Init()
{
	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);

	CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, systemInfo.dwNumberOfProcessors * 2);
}

void IocpSession::Release()
{
}

DWORD IocpSession::AccepThread(LPVOID p)
{
	return 0;
}

bool IocpSession::CreateListenSock()
{
	/*sock_ = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, NULL, WSA_FLAG_OVERLAPPED);
	if (sock_ == INVALID_SOCKET)
	{
		cout << "[ERROR] Failed create ListenSocket";
		return false;
	}

	int reUseAddr = 1;
	setsockopt(sock_, SOL_SOCKET, SO_REUSEADDR, (char *)&reUseAddr, (int)sizeof(reUseAddr));

	memset(&addr_, 0, sizeof(addr_));
	addr_.sin_family = AF_INET;
	addr_.sin_port = htons(port_);
	inet_pton(AF_INET, ip_, &(addr_.sin_addr));

	int retVal = ::bind(sock_, (SOCKADDR*)&addr_, sizeof(addr_));
	if (retVal == SOCKET_ERROR)
	{
		cout << "[ERROR] Failed bind ListenSocket";
		return false;
	}

	retVal = listen(sock_, SOMAXCONN);
	if (retVal == SOCKET_ERROR)
	{
		cout << "[ERROR] Failed listen ListenSocket";
		return false;
	}*/

	return true;
}
