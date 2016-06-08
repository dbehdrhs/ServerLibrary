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
	Release();
}

void IocpSession::Init()
{
	ioData_[IO_SEND].Init();
	ioData_[IO_RECV].Init();
}

void IocpSession::Release()
{
	SessionManager::Instance().CloseSession(this);
}

void IocpSession::OnSend()
{
}

void IocpSession::ReadyRecv()
{
	DWORD flags = 0;
	DWORD recvBytes;

	ioData_[IO_RECV].Init();

	DWORD errCode = WSARecv(sock_, &ioData_[IO_RECV].wsaBuf(), 1, &recvBytes, &flags, &ioData_[IO_RECV].overlapped(), NULL);

	if (errCode == SOCKET_ERROR && (WSAGetLastError() != ERROR_IO_PENDING))
	{
		// ERROR
		cout << "socket error : " << WSAGetLastError() << endl;
	}
}

void IocpSession::OnRecv()
{
	this->ReadyRecv();
}