#include "../imgui/imgui.h"

void PSTree();

void PSTab() {
    if (ImGui::BeginTabItem("颗粒体系")) {

        PSTree();

        ImGui::EndTabItem();
    }
}