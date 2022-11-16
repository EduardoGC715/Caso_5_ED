#pragma once
#include <iostream>
#include"BP_Node.h"

template <typename T>
class BP_Tree {
    BP_Node<T>* m_root;
    std::size_t m_degree;

public:
    BP_Tree(std::size_t _degree) {// Constructor
        m_root = nullptr;
        m_degree = _degree;
    }
    ~BP_Tree() { // Destructor
        clear(m_root);
    }

    BP_Node<T>* getroot(){
        return m_root;
    }

    BP_Node<T>* BPlusTreeSearch(BP_Node<T>* node, T key){
        if(node == nullptr) { // if m_root is null, return nullptr
            return nullptr;
        }
        else{
            BP_Node<T>* cursor = node; // cursor finding key

            while(!cursor->m_is_leaf){ // until cusor pointer arrive leaf
                for(int i=0; i<cursor->m_size; i++){ //in this index node, find what we want key
                    if(key < cursor->m_item[i]){ //find some range, and let find their child also.
                        cursor = cursor->m_children[i];
                        break;
                    }
                    if(i == (cursor->m_size) - 1){
                        cursor = cursor->m_children[i + 1];
                        break;
                    }
                }
            }

            //search for the key if it exists in leaf node.
            for(int i=0; i<cursor->m_size; i++){
                if(cursor->m_item[i] == key){
                    return cursor;
                }
            }

            return nullptr;
        }
    }
    BP_Node<T>* BPlusTreeRangeSearch(BP_Node<T>* node, T key){
        if(node == nullptr) { // if m_root is null, return nullptr
            return nullptr;
        }
        else{
            BP_Node<T>* cursor = node; // cursor finding key

            while(!cursor->m_is_leaf){ // until cusor pointer arrive leaf
                for(int i=0; i<cursor->m_size; i++){ //in this index node, find what we want key
                    if(key < cursor->m_item[i]){ //find some range, and let find their child also.
                        cursor = cursor->m_children[i];
                        break;
                    }
                    if(i == (cursor->m_size) - 1){
                        cursor = cursor->m_children[i + 1];
                        break;
                    }
                }
            }
            return cursor;
        }
    }
    bool search(T data) {  // Return true if the m_item exists. Return false if it does not.
        return BPlusTreeSearch(this->m_root, data) != nullptr;
    }

    int find_index(T* arr, T data, int len){
        int index = 0;
        for(int i=0; i<len; i++){
            if(data < arr[i]){
                index = i;
                break;
            }
            if(i==len-1){
                index = len;
                break;
            }
        }
        return index;
    }
    T* item_insert(T* arr, T data, int len){
        int index = 0;
        for(int i=0; i<len; i++){
            if(data < arr[i]){
                index = i;
                break;
            }
            if(i==len-1){
                index = len;
                break;
            }
        }

        for(int i = len; i > index; i--){
            arr[i] = arr[i-1];
        }

        arr[index] = data;

        return arr;
    }
    BP_Node<T>** child_insert(BP_Node<T>** child_arr, BP_Node<T>*child,int len,int index){
        for(int i= len; i > index; i--){
            child_arr[i] = child_arr[i - 1];
        }
        child_arr[index] = child;
        return child_arr;
    }
    BP_Node<T>* child_item_insert(BP_Node<T>* node, T data, BP_Node<T>* child){
        int item_index=0;
        int child_index=0;
        for(int i=0; i< node->m_size; i++){
            if(data < node->m_item[i]){
                item_index = i;
                child_index = i+1;
                break;
            }
            if(i== node->m_size - 1){
                item_index = node->m_size;
                child_index = node->m_size + 1;
                break;
            }
        }
        for(int i = node->m_size; i > item_index; i--){
            node->m_item[i] = node->m_item[i - 1];
        }
        for(int i= node->m_size + 1; i > child_index; i--){
            node->m_children[i] = node->m_children[i - 1];
        }

        node->m_item[item_index] = data;
        node->m_children[child_index] = child;

        return node;
    }
    void InsertPar(BP_Node<T>* par,BP_Node<T>* child, T data){
        //overflow check
        BP_Node<T>* cursor = par;
        if(cursor->m_size < this->m_degree - 1){//not overflow, just insert in the correct position
            //insert m_item, child, and reallocate
            cursor = child_item_insert(cursor,data,child);
            cursor->m_size++;
        }
        else{//overflow
            //make new node
            auto* Newnode = new BP_Node<T>(this->m_degree);
            Newnode->m_parent = cursor->m_parent;

            //copy m_item
            T* item_copy = new T[cursor->m_size + 1];
            for(int i=0; i<cursor->m_size; i++){
                item_copy[i] = cursor->m_item[i];
            }
            item_copy = item_insert(item_copy,data,cursor->m_size);

            auto** child_copy = new BP_Node<T>*[cursor->m_size + 2];
            for(int i=0; i< cursor->m_size + 1; i++){
                child_copy[i] = cursor->m_children[i];
            }
            child_copy[cursor->m_size + 1] = nullptr;
            child_copy = child_insert(child_copy, child, cursor->m_size + 1, find_index(item_copy, data, cursor->m_size + 1));

            //split nodes
            cursor->m_size = (this->m_degree) / 2;
            if((this->m_degree) % 2 == 0){
                Newnode->m_size = (this->m_degree) / 2 - 1;
            }
            else{
                Newnode->m_size = (this->m_degree) / 2;
            }

            for(int i=0; i<cursor->m_size; i++){
                cursor->m_item[i] = item_copy[i];
                cursor->m_children[i] = child_copy[i];
            }
            cursor->m_children[cursor->m_size] = child_copy[cursor->m_size];

            for(int i=0; i < Newnode->m_size; i++){
                Newnode->m_item[i] = item_copy[cursor->m_size + i + 1];
                Newnode->m_children[i] = child_copy[cursor->m_size + i + 1];
                Newnode->m_children[i]->m_parent=Newnode;
            }
            Newnode->m_children[Newnode->m_size] = child_copy[cursor->m_size + Newnode->m_size + 1];
            Newnode->m_children[Newnode->m_size]->m_parent=Newnode;

            T paritem = item_copy[this->m_degree / 2];

            delete[] item_copy;
            delete[] child_copy;

            //m_parent check
            if(cursor->m_parent == nullptr){//if there are no m_parent node(m_root case)
                auto* Newparent = new BP_Node<T>(this->m_degree);
                cursor->m_parent = Newparent;
                Newnode->m_parent = Newparent;

                Newparent->m_item[0] = paritem;
                Newparent->m_size++;

                Newparent->m_children[0] = cursor;
                Newparent->m_children[1] = Newnode;

                this->m_root = Newparent;

                //delete Newparent;
            }
            else{//if there already have m_parent node
                InsertPar(cursor->m_parent, Newnode, paritem);
            }
        }
    }
    void insert(T t_data) {
        if(m_root == nullptr){ //if the tree is empty
            m_root = new BP_Node<T>(m_degree);
            m_root->set_is_leaf(true);
            m_root->set_item(0,new std::string(t_data));
            m_root->set_size(1); //
        }
        else{ //if the tree has at least one node
            BP_Node<T>* cursor = m_root;

            //move to leaf node
            cursor = BPlusTreeRangeSearch(cursor, t_data);

            //overflow check
            if(cursor->get_size() < (m_degree - 1)){ // not overflow, just insert in the correct position
                //m_item insert and rearrange
                cursor->m_item = item_insert(cursor->m_item, t_data, cursor->m_size);
                cursor->m_size++;
                //edit pointer(next node)
                cursor->m_children[cursor->m_size] = cursor->m_children[cursor->m_size - 1];
                cursor->m_children[cursor->m_size - 1] = nullptr;
            }
            else{//overflow case
                //make new node
                auto* Newnode = new BP_Node<T>(this->m_degree);
                Newnode->m_is_leaf = true;
                Newnode->m_parent = cursor->m_parent;

                //copy m_item
                T* item_copy = new T[cursor->m_size + 1];
                for(int i=0; i<cursor->m_size; i++){
                    item_copy[i] = cursor->m_item[i];
                }

                //insert and rearrange
                item_copy = item_insert(item_copy, t_data, cursor->m_size);

                //split nodes
                cursor->m_size = (this->m_degree) / 2;
                if((this->m_degree) % 2 == 0){
                    Newnode->m_size = (this->m_degree) / 2;
                }
                else{
                    Newnode->m_size = (this->m_degree) / 2 + 1;
                }

                for(int i=0; i<cursor->m_size; i++){
                    cursor->m_item[i] = item_copy[i];
                }
                for(int i=0; i < Newnode->m_size; i++){
                    Newnode->m_item[i] = item_copy[cursor->m_size + i];
                }

                cursor->m_children[cursor->m_size] = Newnode;
                Newnode->m_children[Newnode->m_size] = cursor->m_children[this->m_degree - 1];
                cursor->m_children[this->m_degree - 1] = nullptr;

                delete[] item_copy;

                //m_parent check
                T paritem = Newnode->m_item[0];

                if(cursor->m_parent == nullptr){//if there are no m_parent node(m_root case)
                    auto* Newparent = new BP_Node<T>(this->m_degree);
                    cursor->m_parent = Newparent;
                    Newnode->m_parent = Newparent;

                    Newparent->m_item[0] = paritem;
                    Newparent->m_size++;

                    Newparent->m_children[0] = cursor;
                    Newparent->m_children[1] = Newnode;

                    this->m_root = Newparent;
                }
                else{//if there already have m_parent node
                    InsertPar(cursor->m_parent, Newnode, paritem);
                }
            }
        }
    }

    void clear(BP_Node<T>* cursor){
        if(cursor != nullptr){
            if(!cursor->m_is_leaf){
                for(int i=0; i <= cursor->m_size; i++){
                    clear(cursor->m_children[i]);
                }
            }
            delete[] cursor->m_item;
            delete[] cursor->m_children;
            delete cursor;
        }
    }
    void bpt_print(){
        print(this->m_root, 0);
    }
    void print(BP_Node<T>* cursor,int level) {
        // You must NOT edit this function.
        if (cursor != NULL) {
            for (int i = 0; i < cursor->m_size; ++i) {
                std::cout << cursor->m_item[i] << " ";
            }
            std::cout <<"level:"<<level++<< "\n";

            if (!cursor->m_is_leaf) {
                for (int i = 0; i < cursor->m_size + 1; ++i) {
                    print(cursor->m_children[i], level);
                }
            }
        }
    }
};