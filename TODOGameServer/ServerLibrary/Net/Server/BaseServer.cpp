#include "stdafx.h"
#include "BaseServer.h"

BaseServer::BaseServer()
{
	xml_t config;
	if (!Init(config))
	{

	}
}

BaseServer::~BaseServer()
{
	Release();
}

bool BaseServer::Init(xml_t config)
{
	status_ = SERVER_STOP;

	if (!LoadConfig(&config))
	{
		return false;
	}

	xmlNode_t* root = config.FirstChildElement("App")->FirstChildElement("Server");
	if (!root)
	{
		cout << "[ERROR] not exist process setting" << endl;
		return false;
	}
	
	xmlNode_t* elem = root->FirstChildElement("IP");
	strcpy_s(ip_, elem->GetText());

	elem = root->FirstChildElement("Port");
	sscanf_s(elem->GetText(), "%d", &port_);

	elem = root->FirstChildElement("ThreadCount");
	sscanf_s(elem->GetText(), "%d", &workerThreadCount_);
	
	root = config.FirstChildElement("App");
	elem = root->FirstChildElement("Name");
	printf("[INFO] Start %s Server", elem->GetText());

	status_ = SERVER_INITIALIZE;

	return true;
}

void BaseServer::Release()
{
	status_ = SERVER_STOP;

	cout << "[INFO] BaseServer End" << endl;
}