#pragma once

#include <iostream>
//# include "iNode.h"

template<typename T>
class BP_Node {
private:
    bool m_is_leaf;
    int m_degree; // maximum number of children
    int m_size; // current number of items
    T* m_keys;
    BP_Node<T>** m_children;
    BP_Node<T>* m_parent;
public:
    BP_Node(int t_degree) {
        m_is_leaf = false;
        m_degree = t_degree;
        m_size = 0;

        T* aux_keys = new T[m_degree-1];
        for(int i=0; i<m_degree-1; i++){
            aux_keys[i] = 0;
        }
        m_keys = aux_keys;

        BP_Node<T>** aux_children = new BP_Node<T>*[m_degree];
        for(int i=0; i<m_degree; i++){
            aux_children[i] = nullptr;
        }
        m_children = aux_children;
        m_parent = nullptr;
    }

    void set_is_leaf(bool t_value){
        m_is_leaf=t_value;
    }
    bool get_is_leaf(){
        return m_is_leaf;
    }

    void set_size(int t_size){
        m_size=t_size;
    }
    int get_size(){
        return m_size;
    }

    void set_keys(T* t_keys){
        m_keys=t_keys;
    }
    T* get_keys(){
        return m_keys;
    }

    void set_children(BP_Node<T>** t_children){
        m_children=t_children;
    }
    BP_Node<T>** get_children(){
        return m_children;
    }

    void set_parent(BP_Node<T>* t_parent){
        m_parent=t_parent;
    }
    BP_Node<T>* get_parent(){
        return m_parent;
    }

};