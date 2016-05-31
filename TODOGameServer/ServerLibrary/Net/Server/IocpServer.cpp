#include "stdafx.h"
#include "IocpServer.h"


IocpServer::IocpServer()
{
}

IocpServer::~IocpServer()
{
}

void IocpServer::Init()
{
	CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, workerThreadCount_);
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

bool IocpServer::OnAccept()
{
	return false;
}

bool IocpServer::OnRecv()
{
	// enqueue
	return false;
}