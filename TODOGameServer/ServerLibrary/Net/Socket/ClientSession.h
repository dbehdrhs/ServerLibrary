#pragma once
#include "BaseSocket.h"

class ClientSession : public BaseSocket
{
public:
	ClientSession();
	virtual ~ClientSession();

	// BaseSocket��(��) ���� ��ӵ�
	virtual void OnRecv() override;
};