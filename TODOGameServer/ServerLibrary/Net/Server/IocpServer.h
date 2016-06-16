#pragma once
#include "BaseServer.h"

#define MAX_IOCP_THREAD_COUNT		SIZE_64

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

	void run();

	void serverEnd();

	bool OnAccept(SOCKET clientSock, SOCKADDR_IN clientAddr);
	// AcceptThread
	// WorkerThread

	HANDLE Iocp() { return iocp_; }

	static DWORD WINAPI AcceptThread(PVOID pParam);
	static DWORD WINAPI WorkerThread(PVOID pParam);

private:
	bool AssociateSession(IocpSession* session);

private:
	HANDLE iocp_;

	Thread* acceptThread_;
	array<Thread*, MAX_IOCP_THREAD_COUNT> workerThread_;
};


