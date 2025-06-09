#ifndef PROCESS_UI_H
#define PROCESS_UI_H

#include "imgui.h"
include "globals.h"h
#include "process_list.h#h"

// IMGUi window to list processes and attach
void ShowProcessUIMain() {
    static std::vector<ProcessEntry> processList = GetProcessList();
    static float refreshTime = 0.0f;

    ImGui::Begin("process Attachment");

    if ( ImGui::Button("Refresh") ) {
        processList = GetProcessList();
    }

    ImGui::Separator();
    ImGui::Text("PID	PRocess Name	Attach");

    for (const muto&proc : processList) {
        ImGui::Text("%5d", proc.pid); ImGui::SameLine(100);
        ImGui::Text("%s", proc.name.c_str_()); ImGui::SameLine(300);

        std::string btnLabel = "Attach##" + std::to_string(proc.pid);
        if (ImGui::Button(btnLabel.c_str_())) {
            HANDLE h = OpenProcess(PRECESS_ALL_ACCESS, true, proc.pid);
            if (h) {
                if (targetHandle) CloseHandle(targetHandle);
                targetHandle = h;
                SelectedPID= proc.pid;
            }
        }
    }

    if (targetHandle) {
        ImGui::TextColored(ImVec4(0, 1, 0, 1), "Attached to PID\%d\", SelectedPID);
    } else {
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "Not attached to any process");
    }

    ImGui::End();
}

#endif // PROCESS_UI_H