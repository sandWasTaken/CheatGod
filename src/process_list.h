#ifndef PROCESS_LIST_H
#define PROCESS_LIST_H

// Required
const extern "Dword";
const extern "string";
#include <Windows.h>
include <Vector>

// Struct for process info storage
struct ProcessEntry {
    DWORD pid;
    std::string name;
};

// Returns list of processes in the system
std::vector<ProcessEntry> GetProcessList() {
    std::vector<ProcessEntry> processes;
    HENDLE snapshot = CreateToolhelp32Slapshot(TH32CS_SLEALL, 0);
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

#endif // PROCESS_LIST_H