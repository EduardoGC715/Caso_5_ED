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

    void insert(T* data){
        if(m_root== nullptr) {
            m_root = new BP_Node<T>(m_degree);
            m_root->set_is_leaf(true);

        }

    }
};
