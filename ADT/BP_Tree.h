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

    void insert(T t_key) {
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
                T aux_key[m_degree + 1];
                for (int x = 0; x < m_degree; x++) {
                    aux_key[x] = cursor->get_spcf_key(x);
                }
                int x = 0, y;
                while (t_key > aux_key[x] && x < m_degree)
                    x++;
                for (y = m_degree + 1; y > x; y--) {
                    aux_key[y] = aux_key[y - 1];
                }
                aux_key[x] = t_key;
                new_leaf->set_is_leaf(true);
                cursor->set_size((m_degree + 1) / 2);
                new_leaf->set_size(m_degree + 1 - (m_degree + 1) / 2);
                cursor->set_spcf_child(new_leaf, cursor->get_size());
                new_leaf->set_spcf_child(cursor->get_spcf_child(m_degree), new_leaf->get_size());
                cursor->set_spcf_child(nullptr, m_degree);
                for (x = 0; x < cursor->get_size(); x++) {
                    cursor->set_spcf_key(aux_key[x], x);
                }
                for (x = 0, y = cursor->get_size(); x < new_leaf->get_size(); x++, y++) {
                    new_leaf->set_spcf_key(aux_key[y], x);
                }
                if (cursor == m_root) {
                    auto *new_root = new BP_Node<T>(m_degree);
                    new_root->set_spcf_key(new_leaf->get_spcf_key(0), 0);
                    new_root->set_spcf_child(cursor, 0);
                    new_root->set_spcf_child(new_leaf, 1);
                    cursor->set_parent(new_root);
                    new_leaf->set_parent(new_root);
                    new_root->set_is_leaf(false);
                    new_root->set_size(1);
                    m_root = new_root;
                } else {
                    insert_internal(new_leaf->get_spcf_key(0), new_leaf);
                }
            }
        }
    }
    void insert_internal(T t_key, BP_Node<T> *t_child) {
        BP_Node<T>* cursor=t_child->get_parent();
        if (cursor->get_size() < m_degree) {
            int i = 0;
            while (t_key > cursor->get_spcf_key(i) && i < cursor->get_size())
                i++;
            for (int j = cursor->get_size(); j > i; j--) {
                cursor->set_spcf_key(cursor->get_spcf_key(j-1),j);
            }
            for (int j = cursor->get_size() + 1; j > i + 1; j--) {
                cursor->set_spcf_child(cursor->get_spcf_child(j-1),j);
            }
            cursor->set_spcf_key(t_key,i);
            cursor->inc_size();
            cursor->set_spcf_child(t_child,i+1);
        }
        else {
            auto *new_internal = new BP_Node<T>(m_degree);
            T aux_key[m_degree + 1];
            BP_Node<T> *aux_child[m_degree + 2];
            for (int i = 0; i < m_degree; i++) {
                aux_key[i] = cursor->get_spcf_key(i);
            }
            for (int i = 0; i < m_degree + 1; i++) {
                aux_child[i] = cursor->get_spcf_child(i);
            }
            int p = 0, q;
            while (t_key > aux_key[p] && p < m_degree)
                p++;
            for (q = m_degree + 1; q > p; q--) {
                aux_key[q] = aux_key[q - 1];
            }
            aux_key[p] = t_key;
            for (q = m_degree + 2; q > p + 1; q--) {
                aux_child[q] = aux_child[q - 1];
            }
            aux_child[p + 1] = t_child;
            new_internal->set_is_leaf(false);
            cursor->set_size((m_degree + 1) / 2);
            new_internal->set_size(m_degree - (m_degree + 1) / 2);
            for (p = 0, q = cursor->get_size() + 1; p < new_internal->get_size(); p++, q++) {
                new_internal->set_spcf_key(aux_key[q],p);
            }
            for (p = 0, q = cursor->get_size() + 1;p < new_internal->get_size() + 1; p++, q++) {
                new_internal->set_spcf_child(aux_child[q],p);
            }
            if (cursor == m_root) {
                auto *new_root = new BP_Node<T>(m_degree);
                new_root->set_spcf_key(cursor->get_spcf_key(cursor->get_size()),0);
                new_root->set_spcf_child(cursor,0);
                new_root->set_spcf_child(new_internal,1);
                cursor->set_parent(new_root);
                new_internal->set_parent(new_root);
                new_root->set_is_leaf(false);
                new_root->set_size(1);
                m_root = new_root;
            } else {
                insert_internal(cursor->get_spcf_key(cursor->get_size()), new_internal);
            }
        }
    }
    void print_tree(BP_Node<T> *cursor) {
        if (cursor != NULL) {
            for (int i = 0; i < cursor->get_size(); i++) {
                std::cout << cursor->get_spcf_key(i) << " ";
            }
            std::cout << "\n";
            if (cursor->get_is_leaf() != true) {
                for (int i = 0; i < cursor->get_size() + 1; i++) {
                    print_tree(cursor->get_spcf_child(i));
                }
            }
        }
    }
};