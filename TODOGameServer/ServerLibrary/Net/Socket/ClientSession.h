#pragma once
#include "BaseSocket.h"

class ClientSession : public BaseSocket
{
public:
	ClientSession();
	virtual ~ClientSession();

	ClientSession(int id);

	// BaseSocket��(��) ���� ��ӵ�
	virtual void OnRecv() override;
};