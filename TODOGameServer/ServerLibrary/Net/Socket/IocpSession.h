#pragma once
#include "BaseSocket.h"

class IocpSession :	public BaseSocket
{
public:
	IocpSession();
	virtual ~IocpSession();

	// Inherited via BaseSocket
	virtual void OnRecv() override;

	void Init();
	void Release();

	DWORD WINAPI AccepThread(LPVOID p);

private:
	bool CreateListenSock();

private:
	HANDLE iocp_;

	char ip_[16];
	int port_;
};

