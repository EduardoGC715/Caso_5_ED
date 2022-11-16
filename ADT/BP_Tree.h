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
            while (!cursor->get_is_leaf()) {
                for (int i = 0; i < cursor->get_size(); i++) {
                    if (x < cursor->get_key(i)) {
                        cursor = cursor->get_child(i);
                        break;
                    }
                    if (i == cursor->get_size() - 1) {
                        cursor = cursor->get_child(i + 1);
                        break;
                    }
                }
            }
            for (int i = 0; i < cursor->get_size(); i++) {
                if (cursor->get_key(i) == x) {
                    return cursor;
                }
            }
            return nullptr;
        }
    }

    void insert(T* t_key) {
        if (m_root == NULL) {
            m_root = new BP_Node<T>(m_degree);
            m_root->set_key(t_key, 0);
            m_root->set_is_leaf(true);
            m_root->inc_size();

        } else {
            BP_Node<T> *cursor = m_root;
            BP_Node<T> *parent;
            while (!cursor->get_is_leaf()) {
                parent = cursor;
                for (int i = 0; i < cursor->get_size(); i++) {
                    if (t_key < cursor->get_key(i)) {
                        cursor = cursor->get_child(i);
                        break;
                    }
                    if (i == cursor->get_size() - 1) {
                        cursor = cursor->get_child(i + 1);
                        break;
                    }
                }
            }
            if (cursor->get_size() < m_degree) {
                int i = 0;
                while (t_key > cursor->get_key(i) && i < cursor->get_size())
                    i++;
                for (int j = cursor->get_size(); j > i; j--) {
                    cursor->set_key(cursor->get_key(j - 1), j);
                }
                cursor->set_key(t_key, i);
                cursor->inc_size();
                cursor->set_child(cursor->get_child(cursor->get_size() - 1), cursor->get_size());
                cursor->set_child(nullptr, cursor->get_size() - 1);
            }
            else {
                auto *new_leaf = new BP_Node<T>(m_degree);
                T* aux_keys[m_degree + 1];
                for (int i = 0; i < m_degree; i++) {
                    aux_keys[i] = cursor->get_key(i);
                }
                int i = 0, j;
                while (t_key > aux_keys[i] && i < m_degree)
                    i++;
                for (int j = m_degree + 1; j > i; j--) {
                    aux_keys[j] = aux_keys[j - 1];
                }
                aux_keys[i] = t_key;
                new_leaf->set_is_leaf(true);
                cursor->set_size((m_degree + 1) / 2);
                new_leaf->set_size(m_degree + 1 - (m_degree + 1) / 2);
                cursor->set_child(new_leaf, cursor->get_size());
                new_leaf->set_child(cursor->get_child(m_degree), new_leaf->get_size());
                cursor->set_child(nullptr, m_degree);
                for (i = 0; i < cursor->get_size(); i++) {
                    cursor->set_key(aux_keys[i], i);
                }
                for (i = 0, j = cursor->get_size(); i < new_leaf->get_size(); i++, j++) {
                    new_leaf->set_key(aux_keys[j], i);
                }
                if (cursor == m_root) {
                    auto *new_root = new BP_Node<T>(m_degree);
                    new_root->set_key(new_leaf->get_key(0), 0);
                    new_root->set_child(cursor, 0);
                    new_root->set_child(new_leaf, 1);
                    cursor->set_parent(new_root);
                    new_leaf->set_parent(new_root);
                    new_root->set_is_leaf(false);
                    new_root->set_size(1);
                    m_root = new_root;
                } else {
                    insert_internal(new_leaf->get_key(0), parent, new_leaf);
                }
            }
        }
    }
    void insert_internal(T* t_key,BP_Node<T> *t_parent,BP_Node<T> *t_child) {
        if (t_parent->get_size() < m_degree) {
            int i = 0;
            while (t_key > t_parent->get_key(i) && i < t_parent->get_size())
                i++;
            for (int j = t_parent->get_size(); j > i; j--) {
                t_parent->set_key(t_parent->get_key(j - 1), j);
            }
            for (int j = t_parent->get_size() + 1; j > i + 1; j--) {
                t_parent->set_child(t_parent->get_child(j - 1), j);
            }
            t_parent->set_key(t_key, i);
            t_parent->inc_size();
            t_parent->set_child(t_child, i + 1);
        }
        else {
            auto *new_internal = new BP_Node<T>(m_degree);
            T* aux_keys[m_degree + 1];
            BP_Node<T> *aux_children[m_degree + 2];
            for (int i = 0; i < m_degree; i++) {
                aux_keys[i] = t_parent->get_key(i);
            }
            for (int i = 0; i < m_degree + 1; i++) {
                aux_children[i] = t_parent->get_child(i);
            }
            int i = 0, j;
            while (t_key > aux_keys[i] && i < m_degree)
                i++;
            for (int j = m_degree + 1; j > i; j--) {
                aux_keys[j] = aux_keys[j - 1];
            }
            aux_keys[i] = t_key;
            for (int j = m_degree + 2; j > i + 1; j--) {
                aux_children[j] = aux_children[j - 1];
            }
            aux_children[i + 1] = t_child;
            new_internal->set_is_leaf(false);
            t_parent->set_size((m_degree + 1) / 2);
            new_internal->set_size(m_degree - (m_degree + 1) / 2);
            for (i = 0, j = t_parent->get_size() + 1; i < new_internal->get_size(); i++, j++) {
                new_internal->set_key(aux_keys[j], i);
            }
            for (i = 0, j = t_parent->get_size() + 1; i < new_internal->get_size() + 1; i++, j++) {
                new_internal->set_child(aux_children[j], i);
            }
            if (t_parent == m_root) {
                auto *new_root = new BP_Node<T>(m_degree);
                new_root->set_key(t_parent->get_key(t_parent->get_size()), 0);
                new_root->set_child(t_parent, 0);
                new_root->set_child(new_internal, 1);
                t_parent->set_parent(new_root);
                new_internal->set_parent(new_root);
                new_root->set_is_leaf(false);
                new_root->set_size(1);
                m_root = new_root;
            } else {
                insert_internal(t_parent->get_key(t_parent->get_size()), t_parent->get_parent(), new_internal);
            }
        }
    }
    void print_tree(BP_Node<T> *cursor,int level) {
        if (cursor != NULL) {
            for (int i = 0; i < cursor->get_size(); i++) {
                std::cout << *cursor->get_key(i) << " ";
            }
            std::cout <<" level:"<<level++<< "\n";
            if (cursor->get_is_leaf() != true) {
                for (int i = 0; i < cursor->get_size() + 1; i++) {
                    print_tree(cursor->get_child(i), level);
                }
            }
        }
    }
};