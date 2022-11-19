# pragma once
# include "TreeNode.h"

template<typename T>
class Tree {
    private:
        int size;
        TreeNode<T>* root;

    public:
        Tree() {
            size = 0;
            root = nullptr;
        }

        Tree(T* pData) : Tree<T>() {
            insert(pData, root);
        }

        ~Tree() {
            delete root;
        }

        bool is_empty() {
            return !(size);
        }

        TreeNode<T>* get_root() {
            return root;
        }

        int get_size() {
            return size;
        }

        TreeNode<T>* insert(T* pData, TreeNode<T>* pParent) {
            TreeNode<T>* node = new TreeNode<T>(size++, pData);
            if (! is_empty() && pParent != nullptr) {
                pParent->add_child(node);
                node->set_parent(pParent);
            } else {
                root = node;
            }
            return node;
        }
};