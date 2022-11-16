#pragma once

#include <iostream>
#include <string>

template<typename T>
class BP_Node {
private:
    bool m_is_leaf;
    std::size_t m_degree; // maximum number of m_children
    std::size_t m_size; // current number of m_item
    T* m_item;
    BP_Node<T>** m_children;
    BP_Node<T>* m_parent;

public:
    BP_Node(std::size_t _degree) {// Constructor
        m_is_leaf = false;
        m_degree = _degree;
        m_size = 0;

        T* _item = new T[m_degree - 1];
        for(int i=0; i < m_degree - 1; i++){
            _item[i] = "a";
        }
        this->m_item = _item;

        auto** _children = new BP_Node<T>*[m_degree];
        for(int i=0; i < m_degree; i++){
            _children[i] = nullptr;
        }
        m_children = _children;

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

    void set_itm_arr(T* t_item){
        m_item=t_item;
    }
    T* get_itm_arr(){
        return m_item;
    }
    void set_item(int pos, T* t_key){
        m_item[pos]=t_key;
    }
    T* get_item(int pos){
        return m_item[pos];
    }

    void set_child( int pos, BP_Node<T>* t_child){
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