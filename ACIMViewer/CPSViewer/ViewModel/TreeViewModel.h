/**
@版权 (c) 2023, NanJin Normal University
@文件名 TreeViewModel.cpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 分类颗粒数构建核心算法。
@修订历史 2023.7.28 创建
**/

# pragma once

#include <iostream>
#include <stack>

#include "../Model/Tree.h"
#include "MainWidgetViewModel.h"

class TreeViewModel {
private:
    int preIndex = -1;
    ICIMStandard *_CIMStandard; // 场景标准

    // 根据概念和公理构建分类和颗粒树
    void concept2Tree(const std::string &concept, int index, Core::AxiomType axiomType, TreeNode *current) {
        std::stack<std::pair<std::string, TreeNode*>> stack; // 构建栈模拟树递归
        stack.emplace(concept, current); // 传入当前树节点和概念

        while (!stack.empty()) {
            auto [tempConcept, node] = stack.top(); // 弹出当前树节点和概念
            stack.pop();

            auto item = _CIMStandard->getConceptFromCode(tempConcept.c_str());
            node->data = item->getName(); // 将概念名赋值给节点值

            // 获取概念的子类或子颗粒
            for (int i = 0; i < item->getAxiomsCount(); i++) {
                auto axiom = _CIMStandard->getAxiomFromCode(item->getAxiomId(i)->getCode().c_str());

                // 确定公理依据和公理类型
                if (axiom->getBasisId() == index && axiom->getAxiomType() == axiomType) {
                    for (int j = 0; j < axiom->getConceptCount(); j++) {
                        auto child = axiom->getConcept(j);
                        auto newTreeNode = new TreeNode;

                        stack.emplace(child->getCode(), newTreeNode); // 将子类或子颗粒入栈
                        node->children.emplace_back(newTreeNode);
                    }
                    break;
                }
            }
        }
    }


public:
    TreeNode *root;

    explicit TreeViewModel(ICIMStandard *CIMStandard) : root(new TreeNode), _CIMStandard(CIMStandard) {

    }

    // 根据公理依据和公理类型更新树
    void UpdateTree(int index, bool isCS) {
        if (index == preIndex) return;
        preIndex = index;

        root = new TreeNode;

        auto axiomType1 = isCS ? Core::SUPEROF : Core::CONSISTOF;
        auto axiomType2 = isCS ? Core::SUBOF : Core::PARTOF;

        std::vector<std::string> concepts;

        // 首先获取所有父亲节点
        for (int i = 0; i < _CIMStandard->getAxiomsCount(); i++) {
            auto axiom = _CIMStandard->getAxiomFromCode(_CIMStandard->getAxiomCodeFromIndex(i));

            if (axiom->getBasisId() == index && axiom->getAxiomType() == axiomType2) {
                for (int j = 0; j < axiom->getConceptCount(); j++) {
                    auto concept = axiom->getConcept(j);

                    if (std::count(concepts.begin(), concepts.end(), concept->getCode()) == 0) {
                        concepts.emplace_back(concept->getCode());
                    }
                }
            }
        }

        // 判断父亲节点是否某节点的孩子节点，如果是则移除
        for (int i = 0; i < _CIMStandard->getAxiomsCount(); i++) {
            auto axiom = _CIMStandard->getAxiomFromCode(_CIMStandard->getAxiomCodeFromIndex(i));

            if (axiom->getBasisId() == index && axiom->getAxiomType() == axiomType1) {
                for (int j = 0; j < axiom->getConceptCount(); j++) {
                    auto concept = axiom->getConcept(j);

                    if (std::count(concepts.begin(), concepts.end(), concept->getCode()) != 0) {
                        auto it = std::find(concepts.begin(), concepts.end(), concept->getCode());
                        concepts.erase(it);
                    }
                }
            }
        }

        root->data = "根"; // 防止无概念根，因此增加一个根节点
        // 遍历所有的概念根节点
        for (const auto &concept: concepts) {
            auto newTreeNode = new TreeNode;
            concept2Tree(concept, index, axiomType1, newTreeNode);

            root->children.emplace_back(newTreeNode);
        }
    }
};