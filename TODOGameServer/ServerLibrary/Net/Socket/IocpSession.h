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
		this->Init();
	}

	void Init()
	{
		buffer_.fill(0);

		wBuf_.buf = buffer_.data();
		wBuf_.len = SIZE_IO_MAX;
	}

	IO_TYPE& type() { return type_; }
	char* data() { return buffer_.data(); }
	WSABUF& wsaBuf() { return wBuf_; }
	OVERLAPPED& overlapped() { return overlapped_; }
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

	void ReadyRecv();

private:
	IoData ioData_[IO_END];
};

