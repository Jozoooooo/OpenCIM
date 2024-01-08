#include <stack>

#include "../imgui/imgui.h"

#include "../ViewModel/TreeViewModel.h"

extern TreeViewModel *csTreeViewModel;

void DrawTree(TreeNode *root, int indentLevel = 0) {
    if (!root)
        return;

    std::stack<std::pair<TreeNode *, int>> nodeStack;
    nodeStack.emplace(root, indentLevel);

    while (!nodeStack.empty()) {
        auto [currentNode, currentIndent] = nodeStack.top();
        nodeStack.pop();

        // 添加适当数量的空格来表示缩进
        std::string indentStr(currentIndent, ' ');

        if (currentNode->children.empty()) {
            ImGui::Text("%s%s", indentStr.c_str(), currentNode->data.c_str());
        } else {
            ImGui::PushID(currentNode); // 每个节点使用独一无二的 ID

            bool nodeExpanded = ImGui::TreeNodeEx((void *) (intptr_t) currentNode, ImGuiTreeNodeFlags_None, "%s%s",
                                                  indentStr.c_str(), currentNode->data.c_str());

            ImGui::PopID();

            if (nodeExpanded) {
                for (auto it = currentNode->children.rbegin(); it != currentNode->children.rend(); ++it) {
                    nodeStack.emplace(*it, currentIndent + 4); // 每一层缩进增加 4 个空格
                }
                ImGui::TreePop();
            }
        }
    }
}

void CSTree() {
    DrawTree(csTreeViewModel->root);
}