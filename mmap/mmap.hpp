#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <iostream>
#include <string>
#include <string.h>
#include <Psapi.h>



namespace LibLoaderFunc
{
    void LoadLib(std::string processName);
    int FindProcessId(std::string processName);
}