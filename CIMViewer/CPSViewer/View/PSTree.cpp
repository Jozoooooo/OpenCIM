#include "../ViewModel/TreeViewModel.h"

extern TreeViewModel *psTreeViewModel;

void DrawTree(TreeNode* root, int indentLevel = 0);

void PSTree() {
    DrawTree(psTreeViewModel->root);
}