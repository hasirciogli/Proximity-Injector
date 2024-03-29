#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#define dwClientState 0x59F194
#define dwClientState_State  0x108

#include <Windows.h>
#include <urlmon.h>
#include "bypassByte.h"
#include "VBMem.h"
#include "vbypass.h"

#include <filesystem>
#include <functional>
#include <tchar.h>

#include "../mmap/mmap.hpp"
#include <iostream>

#pragma comment (lib, "Urlmon.lib")

bool isProcessRunning(LPCSTR pName) 
{
    HWND hwnd;
    hwnd = FindWindow(NULL, pName);
    if (hwnd != 0) {
        return true;
    }
    else {
        return false;
    }
}

class ProcessMemory
{
public:
    ProcessMemory(const std::string& process_name)
    {
        // Bu fonksiyon, belirtilen i�lem ad�na g�re bir i�lem ID'si d�nd�r�r.
        m_process_id = get_process_id(process_name);

        // Bu fonksiyon, belirtilen i�lem ID'sine sahip i�lemin bellek
        // eri�im haklar�n� al�r.
        m_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_process_id);
        if (!m_handle) {
            throw std::runtime_error("Failed to open process: " + process_name);
        }
    }

    ~ProcessMemory()
    {
        CloseHandle(m_handle);
    }

    template <typename T>
    T read(DWORD address)
    {
        T value;
        ReadProcessMemory(m_handle, reinterpret_cast<void*>(address), &value, sizeof(T), nullptr);
        return value;
    }

    template <typename T>
    void write(DWORD address, T value)
    {
        WriteProcessMemory(m_handle, reinterpret_cast<void*>(address), &value, sizeof(T), nullptr);
    }

private:
    DWORD get_process_id(const std::string& process_name)
    {
        DWORD process_id = 0;
        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (snapshot != INVALID_HANDLE_VALUE) {
            PROCESSENTRY32 process_entry;
            process_entry.dwSize = sizeof(PROCESSENTRY32);
            if (Process32First(snapshot, &process_entry)) {
                do {
                    if (process_name == process_entry.szExeFile) {
                        process_id = process_entry.th32ProcessID;
                        break;
                    }
                } while (Process32Next(snapshot, &process_entry));
            }
            CloseHandle(snapshot);
        }
        return process_id;
    }

public:

    HANDLE m_handle;
    DWORD m_process_id;
};

DWORD dwGetModuleBaseAddress(DWORD dwProcessID, TCHAR* lpszModuleName)
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessID);
    DWORD dwModuleBaseAddress = 0;
    if (hSnapshot != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 ModuleEntry32 = { 0 };
        ModuleEntry32.dwSize = sizeof(MODULEENTRY32);
        if (Module32First(hSnapshot, &ModuleEntry32))
        {
            do
            {
                if (_tcscmp(ModuleEntry32.szModule, lpszModuleName) == 0)   
                {
                    dwModuleBaseAddress = (DWORD)ModuleEntry32.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnapshot, &ModuleEntry32));
        }
        CloseHandle(hSnapshot);
    }
    return dwModuleBaseAddress;
}

void BypassLoader::LoaderLoop()
{

#if 0
#ifndef _DEBUG

    std::cout << "Cheat loading has been started" << std::endl;

    /*

    ProcessMemory mem("csgo.exe");

    while (!GetAsyncKeyState(VK_SPACE))
    {
        auto EngineDLL = dwGetModuleBaseAddress(mem.m_process_id, (TCHAR*)"engine.dll");
        auto EnginePointer = mem.read<DWORD>(EngineDLL + dwClientState);
        auto GameState = mem.read<int>(EnginePointer + dwClientState_State);

        if (true)
        {
            mSocket::cfg::loading_cheat_state = std::to_string(GameState);
            mSocket::cfg::debugLogList.push_front(std::to_string(GameState));
        }
        Sleep(300);
    }
    exit(0);

    */

    try
    {
        std::string err = "";

        if (!BypasFuncs::letsGoBypass((unsigned char*)dataXQB))
        {
            MessageBoxA(0, "Please reopen a loader maybe 5 times, Cause beta loader!!!", "", 0);
            ExitThread(0);
            exit(-1);
        }

        //getchar();

    }
    catch (...)
    {
        MessageBoxA(0, "Please reopen a loader maybe 5 times, Cause beta loader!!!", "", 0);
        ExitThread(0);
        exit(-1);
    }

    std::cout << "Bypassing Valve process (Restart steam etc..)" << std::endl;


    Sleep(2000);

    std::cout << "Checking steam is open...." << std::endl;

    Sleep(1000);

    while (!isProcessRunning("Steam"))
        Sleep(500);

    std::cout << "Yes steam is opened..." << std::endl;

    Sleep(5000);

    std::cout << "Starting csgo, Wait a small second :)" << std::endl;


    system("cmd /c start steam://rungameid/730");

    Sleep(5000);

    std::cout << "Finding csgo process..." << std::endl;

    Sleep(2000);

    while (!LibLoaderFunc::FindProcessId("csgo.exe"))
        Sleep(300);

    std::cout << "Csgo Process found... (Waiting Window...)" << std::endl;


    while (!FindWindowA(0, "Counter-Strike: Global Offensive - Direct3D 9"))
        Sleep(2000);

    Sleep(3000);
    std::cout << "Loading FLB States (Kernel Bypass Funtions)" << std::endl;

    Sleep(2000);
    std::cout << "Injecting FLB...";

    Sleep(3000);
    std::cout << "Checking Bypass Lib's (Kernel Bypass Checking)" << std::endl;

    Sleep(2000);
    std::cout << "Bypass WORK!";

    Sleep(3000);
    std::cout << "Loading Proximity (Kernel Process Lock)" << std::endl;

    Sleep(16000);
#endif

#endif

    //LibraryLoader::inject(LibLoaderFunc::FindProcessId("csgo.exe"), "C:\\Users\\Mustafa_Owner\\Desktop\\Proximity-Csgo-Project\\Proximity_Cheat\\src\\output\\debug\\Proximity.dll");

    LibLoaderFunc::LoadLib("csgo.exe");

    Sleep(1000);

    std::cout << "PROXIMITY IS LOADED LETS F*CKING GO!";

    Sleep(5000);

    exit(0);
}