#pragma once
#include "stdafx.h"

class WSA
{
private:
	WSADATA wsa_;

public:
	WSA()
	{
		static bool init = false;

		if (init)
			return;

		if (WSAStartup(MAKEWORD(2, 2), &wsa_) != 0)
		{
			cout << "[ERROR] WSAStartup Failed" << endl;
			exit(0);
		}

		init = true;
		cout << "[INFO] WSAStartup OK" << endl;
	}
	~WSA()
	{
		WSACleanup();
		cout << "[INFO] WSACleanup OK" << endl;
	}
};

static WSA wsa;