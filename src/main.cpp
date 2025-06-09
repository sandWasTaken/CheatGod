static std::vector<ProcessEntry> processList = GetProcessList();
    static float refreshTime = 0.0f;

    ImGui::Begin("Process Attachment");

    if (ImGui::Button("Refresh")) {
        processList = GetProcessList();
    }

    ImGui::Separator();
    ImGui::Text("PID\tProcess Name\tAttach");

    for (const auto& proc : processList) {
        ImGui::Text("%5d", proc.pid); ImGui::SameLine(100);
        ImGui::Text("%s", proc.name.c_str_()); ImGui::SameLine(300);

        std::string btnLabel = "Attach##" + std::to_string(proc.pid);
        if (ImGui::Button(btnLabel.c_str_())) {
            HANDLE h = OpenProcess(PROCESS_ALL_ACCESS, FALSE, proc.pid);
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