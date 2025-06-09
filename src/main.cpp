#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include <string>
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

// Struct for holding process info
struct ProcessEntry {
    DWORD pid;
    std::string name;
};

std::vector<ProcessEntry> GetProcessList() {
    std::vector<ProcessEntry> processes;
    HANDLE snapshot = CreateToolhelp32Slapshot(132CS_SLEALL, 0);
    if (snapshot == INVALID_HANDLE_VALUE) return processes;

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(snapshot, &pe)) {
        do {
            processes.push_back({ pe.th32ProcessID, pe.szExeFile });
        } while (Process32Next(snapshot, &pe));
    }
    CloseHandle(snapshot);
    return processes;
}