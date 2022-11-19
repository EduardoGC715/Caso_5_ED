# pragma once
# include <vector>
# include "iNode.h"

using std::vector;

template<typename T>
class TreeNode: public iNode<int, T> {
    private:
        TreeNode<T>* parent;
        vector<TreeNode<T>*>* children;

    public:
        TreeNode(int pKey, T* pData) : iNode<int, T>(pKey, pData) {
            parent = nullptr;
            children = new vector<TreeNode<T>*>;
        }

        ~TreeNode() {
            for (int index = 0; index < children->size(); ++index) {
                delete children->at(index);
            }
            children->clear();
            delete children;
        }

        int children_count() {
            return children->size();
        }

        TreeNode<T>* get_parent() {
            return parent;
        }

        void set_parent(TreeNode<T>* pParent) {
            parent = pParent;
        }

        TreeNode<T>* get_child(int pIndex) {
            try {
                return children->at(pIndex);
            } catch (const std::out_of_range& exception) {
                return nullptr;
            }
        }

        void add_child(TreeNode<T>* pNode) {
            int index = 0;
            for (; index < children->size(); ++index) {
                TreeNode<T>* current = get_child(index);
                if (current->get_key() > pNode->get_key()) {
                    break;
                }
            } children->emplace(children->begin() + index, pNode);
        }

        T* remove_child(int pIndex) {
            T* result = nullptr;
            TreeNode<T>* target = get_child(pIndex);
            if (target != nullptr) {
                children->erase(children->begin() + pIndex);
                result = target->get_data();
                delete target;
            }
            return result;
        }
};