#include "../imgui/imgui.h"

#include "../ViewModel/CPSTabControlViewModel.h"
#include "../ViewModel/TreeViewModel.h"

extern CPSTabControlViewModel *cpsTabControlViewModel;
extern TreeViewModel *csTreeViewModel;
extern TreeViewModel *psTreeViewModel;

void CSTab();

void PSTab();

void CPSTabControl(float x, float y, float w, float h) {
    ImGui::SetNextWindowPos(ImVec2(x, y));
    ImGui::SetNextWindowSize(ImVec2(w, h));

    ImGui::Begin("CPSTabControl", nullptr, ImGuiWindowFlags_NoTitleBar);

    std::vector<const char *> temp;

    for (const auto &item: cpsTabControlViewModel->combItem->items) {
        temp.emplace_back(item.c_str());
    }

    ImGui::Combo("公理依据", &cpsTabControlViewModel->combItem->currentItemIndex,
                 temp.data(),
                 static_cast<int>(cpsTabControlViewModel->combItem->items.size()));

    csTreeViewModel->UpdateTree(cpsTabControlViewModel->combItem->currentItemIndex, true);
    psTreeViewModel->UpdateTree(cpsTabControlViewModel->combItem->currentItemIndex, false);

    ImGui::BeginTabBar("分类颗粒体系");

    CSTab();
    PSTab();

    ImGui::EndTabBar();

    ImGui::End();
}