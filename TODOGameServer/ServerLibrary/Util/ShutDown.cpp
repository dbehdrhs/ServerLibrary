#include "stdafx.h"
#include "ShutDown.h"

bool _shutDown = false;
void ShutDownServer()
{
	_shutDown = true;
}