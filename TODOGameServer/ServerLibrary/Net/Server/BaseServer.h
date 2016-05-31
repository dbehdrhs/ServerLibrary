#pragma once
class BaseServer
{
public:
	BaseServer();
	virtual ~BaseServer();

	void Init();
	void Release();

private:
	int port_;
	array<char, 16> ip_;
};

