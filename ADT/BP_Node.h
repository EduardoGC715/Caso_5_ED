#pragma once

#include <iostream>
#include <vector>

template<typename T>
class BP_Node {
private:
    bool m_is_leaf;
    int m_degree; // maximum number of children
    int m_size; // current number of keys
    std::vector<T*> m_keys;
    std::vector<BP_Node<T>*> m_children;
    BP_Node<T>* m_parent;
public:
    BP_Node(int t_degree) {
        m_is_leaf = false;
        m_degree = t_degree;
        m_size = 0;

        for(int i=0; i<m_degree; i++){
            m_keys.push_back(nullptr);
        }

        for(int i=0; i<m_degree+1; i++){
            m_children.push_back(nullptr);
        }
        m_parent = nullptr;
    }

    void set_is_leaf(bool t_bool){
        m_is_leaf=t_bool;
    }
    bool get_is_leaf(){
        return m_is_leaf;
    }

    void inc_size(){
        m_size++;
    }
    void set_size(int t_size){
        m_size=t_size;
    }
    int get_size(){
        return m_size;
    }

    void set_key(T* t_key, int pos){
        m_keys[pos]=t_key;
    }
    T* get_key(int pos){
        return m_keys[pos];
    }

    void set_child(BP_Node<T>* t_child, int pos){
        m_children[pos]=t_child;
    }
    BP_Node<T>* get_child(int pos){
        return m_children[pos];
    }

    void set_parent(BP_Node<T>* t_parent){
        m_parent=t_parent;
    }
    BP_Node<T>* get_parent(){
        return m_parent;
    }

};