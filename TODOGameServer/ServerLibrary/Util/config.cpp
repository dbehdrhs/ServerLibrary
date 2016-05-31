#include "stdafx.h"
#include "config.h"

bool LoadConfig(xml_t * config)
{
	if (!config->LoadFile("config.xml"))
	{
		cout << "not found config.xml" << endl;
		return false;
	}

	return true;
}
