#pragma once

class Thread
{
private:
	HANDLE hThread;
public:
	Thread();
	~Thread();

	void Init();
	void Release();
};

