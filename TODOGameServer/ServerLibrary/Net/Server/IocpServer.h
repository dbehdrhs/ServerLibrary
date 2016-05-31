#pragma once
#include "BaseServer.h"

class IocpServer :	public BaseServer
{
public:
	IocpServer();
	virtual ~IocpServer();

	void Init();
	void Release();

	bool CreateListenSocket();

	// Inherited via BaseServer
	virtual bool OnRecv() override;
	//bool OnSend();

	bool OnAccept();
	// AcceptThread
	// WorkerThread

private:
	HANDLE iocp_;

	SOCKET listenSocket_;
};

