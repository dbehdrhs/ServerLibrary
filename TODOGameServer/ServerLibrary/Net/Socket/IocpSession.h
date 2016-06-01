#pragma once
#include "BaseSocket.h"

enum IO_TYPE
{
	IO_SEND,
	IO_RECV,
	IO_END
};

class IoData
{
private:
	OVERLAPPED overlapped_;
	WSABUF wBuf_;

	array<char, SIZE_IO_MAX> buffer_;
	IO_TYPE type_;

public:
	IoData()
	{
		ZeroMemory(&overlapped_, sizeof(overlapped_));
		this->Clear();
	}

	void Clear()
	{
		buffer_.fill(0);
	}

	IO_TYPE& type() { return type_; }
	char* data() { return buffer_.data(); }
};

class IocpSession :	public BaseSocket
{
public:
	IocpSession();
	IocpSession(SOCKET sock, SOCKADDR_IN addr);
	virtual ~IocpSession();

	void Init();
	void Release();

	// Inherited via BaseSocket
	virtual void OnRecv() override;
	virtual void OnSend() override;

private:
	IoData ioData_[IO_END];
};

