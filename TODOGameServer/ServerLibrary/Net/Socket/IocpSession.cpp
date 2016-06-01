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

void IocpSession::OnRecv()
{
}