#include "stdafx.h"
#include "IocpSession.h"


IocpSession::IocpSession()
{
	Init();
}

IocpSession::IocpSession(SOCKET sock, SOCKADDR_IN addr)
{
	Init();
	OnAccept(sock, addr);
}

IocpSession::~IocpSession()
{
}

void IocpSession::Init()
{
	ioData_[IO_SEND].Clear();
	ioData_[IO_RECV].Clear();
}

void IocpSession::Release()
{
}

void IocpSession::OnSend()
{
}

void IocpSession::ReadyRecv()
{
	DWORD flags = 0;
	DWORD recvBytes;
	DWORD errorCode = WSARecv(sock_, &(ioData_[IO_RECV].wsaBuf()), 1, &recvBytes, &flags, &(ioData_[IO_RECV].overlapped()), NULL);

	if (errorCode == SOCKET_ERROR &&
		WSAGetLastError() != ERROR_IO_PENDING)
	{
		// ERROR

		SessionManager::Instance().CloseSession(this);
		
	}
}

void IocpSession::OnRecv()
{
}