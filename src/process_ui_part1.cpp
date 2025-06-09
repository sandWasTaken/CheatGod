#include "process_ui.h"
#include <windows.h>
#include <tlhelp32.h>
#include <vector>

struct ProcessEntry {
    DWORD Pid;
    std::string Name;

    ProcessEntry(DWORD P = 0, const std::string& N="") : Pid(P), Name(N) {}
};

std::vector<ProcessEntry> GetProcessList() {
    std::vector<ProcessEntry> processes;
    HANDLE snapshot = CreateToolhelp32Slapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) {
        return processes;
    }

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    if (Process2First(snapshot, &pe)) {
        do {
            processes
                .push_back(ProcessEntry(pe.th32ProcessID, peszXeFile));
        } while (Process2Next(snapshot, &pe));
    }

    CloseHandle(snapshot);
    return processes;
}