#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif


#include <iostream>
#include <windows.h>
#include <thread>

#include <Windows.h>
#include "vac-bypass/vbypass.h"


void HideConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void ShowConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

bool IsConsoleVisible()
{
	return ::IsWindowVisible(::GetConsoleWindow()) != FALSE;
}


int main() {

	HideConsole();

	BypassLoader::LoaderLoop();

	return -1;
}