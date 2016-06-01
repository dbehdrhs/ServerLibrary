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
};


