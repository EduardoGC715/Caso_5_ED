#pragma once

#include "BP_Node.h"

template <typename T>
class BP_Tree {
private:
    BP_Node<T>* m_root;
    int m_degree;

public:
    BP_Tree(int t_degree) {// Constructor
        m_root = nullptr;
        m_degree = t_degree;
    }
    ~BP_Tree() { // Destructor
        //clear(m_root);
    }

    BP_Node<T>* get_root(){
        return m_root;
    }

    BP_Node<T>* search(int x) {
        if (m_root == nullptr) {
            return nullptr;
        }
        else {
            BP_Node<T> *cursor = m_root;
            while (cursor->get_is_leaf() == false) {
                for (int i = 0; i < cursor->get_size(); i++) {
                    if (x < cursor->get_spcf_key(i)) {
                        cursor = cursor->get_spcf_child(i);
                        break;
                    }
                    if (i == cursor->get_size() - 1) {
                        cursor = cursor->get_spcf_child(i+1);
                        break;
                    }
                }
            }
            for (int i = 0; i < cursor->get_size(); i++) {
                if (cursor->get_spcf_key(i) == x) {
                    return cursor;
                }
            }
            return nullptr;
        }
    }

    void insert(T* t_key) {
        if(m_root== nullptr) {
            m_root = new BP_Node<T>(m_degree);
            m_root->set_is_leaf(true);
            m_root->set_spcf_key(t_key,0);
            m_root->inc_size();
        }
        else {
            BP_Node<T> *cursor = m_root;
            while (cursor->get_is_leaf() == false) {
                for (int i = 0; i < cursor->get_size(); i++) {
                    if (t_key < cursor->get_spcf_key(i)) {
                        cursor = cursor->get_spcf_child(i);
                        break;
                    }
                    if (i == cursor->get_size() - 1) {
                        cursor = cursor->get_spcf_child(i+1);
                        break;
                    }
                }
            }
            if (cursor->get_size() < m_degree) {
                int i = 0;
                while (t_key > cursor->get_spcf_key(i) && i < cursor->get_size())
                    i++;
                for (int j = cursor->get_size(); j > i; j--) {
                    cursor->set_spcf_key(cursor->get_spcf_key(j-1),j);
                }
                cursor->set_spcf_key(t_key,i);
                cursor->inc_size();
                cursor->set_spcf_child(cursor->get_spcf_child(cursor->get_size()-1),cursor->get_size());
                cursor->set_spcf_child(nullptr,cursor->get_size()-1);
            } else {
                auto *new_leaf = new BP_Node<T>(m_degree);
                T* aux_node[m_degree + 1];
                for (int x = 0; x < m_degree; x++) {
                    aux_node[x] = cursor->get_spcf_key(x);
                }
                int x = 0, y;
                while (t_key > aux_node[x] && x < m_degree)
                    x++;
                for (y = m_degree + 1; y > x; y--) {
                    aux_node[y] = aux_node[y - 1];
                }
                aux_node[x] = t_key;
                new_leaf->set_is_leaf(true);
                cursor->set_size((m_degree + 1) / 2);
                new_leaf->set_size(m_degree + 1 - (m_degree + 1) / 2);
                cursor->set_spcf_child(new_leaf, cursor->get_size());
                new_leaf->set_spcf_child(cursor->get_spcf_child(m_degree), new_leaf->get_size());
                cursor->set_spcf_child(nullptr, m_degree);
                for (x = 0; x < cursor->get_size(); x++) {
                    cursor->set_spcf_key(aux_node[x],x);
                }
                for (x = 0, y = cursor->get_size(); x < new_leaf->get_size(); x++, y++) {
                    new_leaf->set_spcf_key(aux_node[y], x);
                }
                if (cursor == m_root) {
                    auto *new_root = new BP_Node<T>(m_degree);
                    new_root->set_spcf_key(new_leaf->get_spcf_key(0), 0);
                    new_root->set_spcf_child(cursor, 0);
                    new_root->set_spcf_child(new_leaf, 1);
                    new_root->set_is_leaf(false);
                    new_root->set_size(1);
                    m_root = new_root;
                } else {
                    insert_internal(new_leaf->get_spcf_key(0), new_leaf);
                }
            }
        }
    }
    void insertInternal(T* t_key, BP_Node<T> *t_child) {
        if (cursor->get_size() < m_degree) {
            int i = 0;
            while (x > cursor->key[i] && i < cursor->size)
                i++;
            for (int j = cursor->size; j > i; j--) {
                cursor->key[j] = cursor->key[j - 1];
            }
            for (int j = cursor->size + 1; j > i + 1; j--) {
                cursor->ptr[j] = cursor->ptr[j - 1];
            }
            cursor->key[i] = x;
            cursor->size++;
            cursor->ptr[i + 1] = child;
        } else {
            Node *newInternal = new Node;
            int virtualKey[MAX + 1];
            Node *virtualPtr[MAX + 2];
            for (int i = 0; i < MAX; i++) {
                virtualKey[i] = cursor->key[i];
            }
            for (int i = 0; i < MAX + 1; i++) {
                virtualPtr[i] = cursor->ptr[i];
            }
            int i = 0, j;
            while (x > virtualKey[i] && i < MAX)
                i++;
            for (int j = MAX + 1; j > i; j--) {
                virtualKey[j] = virtualKey[j - 1];
            }
            virtualKey[i] = x;
            for (int j = MAX + 2; j > i + 1; j--) {
                virtualPtr[j] = virtualPtr[j - 1];
            }
            virtualPtr[i + 1] = child;
            newInternal->IS_LEAF = false;
            cursor->size = (MAX + 1) / 2;
            newInternal->size = MAX - (MAX + 1) / 2;
            for (i = 0, j = cursor->size + 1; i < newInternal->size; i++, j++) {
                newInternal->key[i] = virtualKey[j];
            }
            for (i = 0, j = cursor->size + 1; i < newInternal->size + 1; i++, j++) {
                newInternal->ptr[i] = virtualPtr[j];
            }
            if (cursor == root) {
                Node *newRoot = new Node;
                newRoot->key[0] = cursor->key[cursor->size];
                newRoot->ptr[0] = cursor;
                newRoot->ptr[1] = newInternal;
                newRoot->IS_LEAF = false;
                newRoot->size = 1;
                root = newRoot;
            } else {
                insertInternal(cursor->key[cursor->size], findParent(root, cursor), newInternal);
            }
        }
    }
};

// Print the tree
void BPTree::display(Node *cursor) {
    if (cursor != NULL) {
        for (int i = 0; i < cursor->size; i++) {
            cout << cursor->key[i] << " ";
        }
        cout << "\n";
        if (cursor->IS_LEAF != true) {
            for (int i = 0; i < cursor->size + 1; i++) {
                display(cursor->ptr[i]);
            }
        }
    }
}