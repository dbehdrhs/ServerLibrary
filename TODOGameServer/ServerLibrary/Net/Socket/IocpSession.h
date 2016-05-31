#pragma once
#include "BaseSocket.h"

enum IOTYPE
{
	IO_READ,
	IO_WRITE,
	IO_END
};

struct overlappedEx : OVERLAPPED
{
	char buffer_[SIZE_IO_MAX];
	IOTYPE type_;
};

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
};

