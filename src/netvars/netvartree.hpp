#ifndef ANIUM_NETVARTREE_HPP
#define ANIUM_NETVARTREE_HPP

#include <string>
#include <utility>
#include <vector>
#include "../interfaces/interfaces.hpp"
#include "../sdk/miscellaneous/Recv.hpp"
#include "../sdk/interfaces/IBaseClientDLL.hpp"
#include "../utils/logging.hpp"

struct TreeNode; // Pre-declare TreeNode

using Tree = std::vector<std::pair<std::string, TreeNode*>>;

struct TreeNode {
    Tree children;
    RecvProp* prop;
};

class NetVarTree {
private:
    Tree tree;

    void Populate(RecvTable* table, Tree* nodes) {
        for (int i = 0; i < table->nProps; i++) {
            RecvProp* prop = &table->pProps[i];
            TreeNode* node = new TreeNode();
            node->prop = prop;

            if (prop->type == 6)
                Populate(prop->dataTable, &node->children);

            nodes->emplace_back(std::pair<std::string, TreeNode*>(prop->name, node));
        }
    }

public:
    void Init() {
        for (ClientClass* clazz = client->GetAllClasses(); clazz != nullptr; clazz = clazz->next) {
            TreeNode* node = new TreeNode();
            node->prop = nullptr;

            Populate(clazz->recvTable, &node->children);

            this->tree.emplace_back(clazz->recvTable->netTableName, node);
        }
    }

    uintptr_t FindOffset(std::vector<std::string> tables) {
        uintptr_t offset = 0;
        Tree nodes = this->tree;

        for (std::string name : tables) {
            Tree oldNodes = nodes;

            for (std::pair<std::string, TreeNode*>& node : nodes) {
                if (node.first.find(name) != std::string::npos) {
                    nodes = node.second->children;

                    if (node.second->prop != nullptr)
                        offset += node.second->prop->offset;

                    break;
                }
            }

            if (nodes == oldNodes)
                logger.log("Unable to find NetVar %s.", name.c_str());
        }

        return offset;
    }

};

#endif  // ANIUM_NETVARTREE_HPP
