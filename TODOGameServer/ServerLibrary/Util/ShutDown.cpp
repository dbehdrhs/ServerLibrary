#include "stdafx.h"
#include "ShutDown.h"

bool g_shutDown = false;
void ShutDownServer()
{
	g_shutDown = true;
}