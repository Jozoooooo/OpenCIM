#include "../imgui/imgui.h"

void CSTree();

void CSTab() {
    if (ImGui::BeginTabItem("分类体系")) {

        CSTree();

        ImGui::EndTabItem();
    }
}