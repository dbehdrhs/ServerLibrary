#pragma once
#include "BaseSocket.h"

class ClientSession : public BaseSocket
{
public:
	ClientSession();
	virtual ~ClientSession();

	ClientSession(int id);

	// BaseSocket을(를) 통해 상속됨
	virtual void OnRecv() override;
};