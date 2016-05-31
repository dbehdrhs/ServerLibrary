#include "stdafx.h"
#include "ClientSession.h"


ClientSession::ClientSession()
{
}


ClientSession::~ClientSession()
{
}

ClientSession::ClientSession(int id)
{
	id_ = id;
}

void ClientSession::OnRecv()
{
}

void ClientSession::OnSend()
{
}
