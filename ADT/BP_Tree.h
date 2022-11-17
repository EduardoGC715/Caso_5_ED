#pragma once
#include <iostream>
#include"BP_Node.h"
#include <vector>

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

    BP_Node<T>* get_root(){
        return m_root;
    }
    void set_root(BP_Node<T>* t_root){
        m_root=t_root;
    }

    BP_Node<T>* BPlusTreeSearch(BP_Node<T>* t_node, T t_key){
        if(t_node == nullptr) { // if m_root is null, return nullptr
            return nullptr;
        }
        else{
            BP_Node<T>* cursor = t_node; // cursor finding t_key

            while(!cursor->get_is_leaf()){ // until cusor pointer arrive leaf
                for(int i=0; i<cursor->get_size(); i++){ //in this index t_node, find what we want t_key
                    if(t_key < cursor->get_item(i)){ //find some range, and let find their child also.
                        cursor = cursor->get_child(i);
                        break;
                    }
                    if(i == (cursor->get_size()) - 1){
                        cursor = cursor->get_child(i+1);
                        break;
                    }
                }
            }

            //search for the t_key if it exists in leaf t_node.
            for(int i=0; i<cursor->get_size(); i++){
                if(cursor->get_item(i) == t_key){
                    return cursor;
                }
            }

            return nullptr;
        }
    }
    BP_Node<T>* BPlusTreeRangeSearch(BP_Node<T>* t_node, T t_key){
        if(t_node == nullptr) { // if m_root is null, return nullptr
            return nullptr;
        }
        else{
            BP_Node<T>* cursor = t_node; // cursor finding t_key

            while(!cursor->get_is_leaf()){ // until cusor pointer arrive leaf
                for(int i=0; i<cursor->get_size(); i++){ //in this index t_node, find what we want t_key
                    if(t_key < cursor->get_item(i)){ //find some range, and let find their child also.
                        cursor = cursor->get_child(i);
                        break;
                    }
                    if(i == (cursor->get_size()) - 1){
                        cursor = cursor->get_child(i+1);
                        break;
                    }
                }
            }
            return cursor;
        }
    }
    bool search(T data) {  // Return true if the m_item exists. Return false if it does not.
        return BPlusTreeSearch(m_root, data) != nullptr;
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
    BP_Node<T>** child_insert(BP_Node<T>** t_child_arr, BP_Node<T>*t_child, int t_len, int t_index){
        for(int i= t_len; i > t_index; i--){
            t_child_arr[i] = t_child_arr[i - 1];
        }
        t_child_arr[t_index] = t_child;
        return t_child_arr;
    }
    BP_Node<T>* child_item_insert(BP_Node<T>* t_node, T t_data, BP_Node<T>* t_child){
        int item_index=0;
        int child_index=0;
        for(int i=0; i < t_node->get_size(); i++){
            if(t_data < t_node->get_item(i)){
                item_index = i;
                child_index = i+1;
                break;
            }
            if(i == t_node->get_size() - 1){
                item_index = t_node->get_size();
                child_index = t_node->get_size() + 1;
                break;
            }
        }
        for(int i = t_node->get_size(); i > item_index; i--){
            t_node->set_item(i, t_node->get_item(i - 1));
        }
        for(int i= t_node->get_size() + 1; i > child_index; i--){
            t_node->set_child(i, t_node->get_child(i - 1));
        }

        t_node->set_item(item_index, t_data);
        t_node->set_child(child_index, t_child);

        return t_node;
    }
    void insert_prnt(BP_Node<T>* par, BP_Node<T>* child, T data){
        //overflow check
        BP_Node<T>* cursor = par;
        if(cursor->get_size() < m_degree - 1){//not overflow, just insert in the correct position
            //insert m_item, child, and reallocate
            cursor = child_item_insert(cursor,data,child);
            cursor->inc_size();
        }
        else{//overflow
            //make new node
            auto* new_node = new BP_Node<T>(m_degree);
            new_node->set_parent(cursor->get_parent());

            //copy m_item
            T* item_copy = new T[cursor->get_size()+ 1];
            for(int i=0; i<cursor->get_size(); i++){
                item_copy[i] = cursor->get_item(i);
            }
            item_copy = item_insert(item_copy,data,cursor->get_size());

            auto** child_copy = new BP_Node<T>*[cursor->get_size() + 2];
            for(int i=0; i< cursor->get_size() + 1; i++){
                child_copy[i] = cursor->get_child(i);
            }
            child_copy[cursor->get_size() + 1] = nullptr;
            child_copy = child_insert(child_copy, child, cursor->get_size() + 1, find_index(item_copy, data, cursor->get_size() + 1));

            //split nodes
            cursor->set_size((m_degree) / 2);
            if((this->m_degree) % 2 == 0){
                new_node->set_size((m_degree) / 2 - 1);
            }
            else{
                new_node->set_size((m_degree) / 2);
            }

            for(int i=0; i<cursor->get_size(); i++){
                cursor->set_item(i,item_copy[i]);
                cursor->set_child(i,child_copy[i]);
            }
            cursor->set_child(cursor->get_size(),child_copy[cursor->get_size()]);

            for(int i=0; i < new_node->get_size(); i++){
                new_node->set_item(i,item_copy[cursor->get_size() + i + 1]);
                new_node->set_child(i,child_copy[cursor->get_size() + i + 1]);
                new_node->get_child(i)->set_parent(new_node);
            }
            new_node->set_child(new_node->get_size(),child_copy[cursor->get_size() + new_node->get_size() + 1]);
            new_node->get_child(new_node->get_size())->set_parent(new_node);

            T prnt_item = item_copy[m_degree / 2];

            delete[] item_copy;
            delete[] child_copy;

            //m_parent check
            if(cursor->get_parent() == nullptr){//if there are no m_parent node(m_root case)
                auto* new_parent = new BP_Node<T>(this->m_degree);
                cursor->set_parent(new_parent);
                new_node->set_parent(new_parent);

                new_parent->set_item(0,prnt_item);
                new_parent->inc_size();

                new_parent->set_child(0,cursor);
                new_parent->set_child(1,new_node);

                m_root = new_parent;

                //delete new_parent;
            }
            else{//if they already have m_parent node
                insert_prnt(cursor->get_parent(), new_node, prnt_item);
            }
        }
    }
    void insert(T t_data) {
        if(m_root == nullptr){ //if the tree is empty
            m_root = new BP_Node<T>(m_degree);
            m_root->set_is_leaf(true);
            m_root->set_item(0,t_data);
            m_root->set_size(1); //
        }
        else{ //if the tree has at least one node
            BP_Node<T>* cursor = m_root;

            //move to leaf node
            cursor = BPlusTreeRangeSearch(cursor, t_data);

            //overflow check
            if(cursor->get_size() < (m_degree - 1)){ // not overflow, just insert in the correct position
                //m_item insert and rearrange
                cursor->set_itm_arr(item_insert(cursor->get_itm_arr(), t_data, cursor->get_size()));
                cursor->inc_size();
                //edit pointer(next node)
                cursor->set_child(cursor->get_size(),cursor->get_child(cursor->get_size()-1));
                cursor->set_child(cursor->get_size()-1, nullptr);
            }
            else{//overflow case
                //make new node
                auto* new_node = new BP_Node<T>(this->m_degree);
                new_node->set_is_leaf(true);
                new_node->set_parent(cursor->get_parent());

                //copy m_item
                T* item_copy = new T[cursor->get_size() + 1];
                for(int i=0; i<cursor->get_size(); i++){
                    item_copy[i] = cursor->get_item(i);
                }

                //insert and rearrange
                item_copy = item_insert(item_copy, t_data, cursor->get_size());

                //split nodes
                cursor->set_size((m_degree) / 2);
                if((m_degree) % 2 == 0){
                    new_node->set_size((m_degree) / 2);
                }
                else{
                    new_node->set_size((m_degree) / 2 + 1);
                }

                for(int i=0; i<cursor->get_size(); i++){
                    cursor->set_item(i,item_copy[i]);
                }
                for(int i=0; i < new_node->get_size(); i++){
                    new_node->set_item(i,item_copy[cursor->get_size() + i]);
                }

                cursor->set_child(cursor->get_size(),new_node);
                new_node->set_child(new_node->get_size(),cursor->get_child(m_degree-1));
                cursor->set_child(m_degree-1,nullptr);

                delete[] item_copy;

                //m_parent check
                T prnt_item = new_node->get_item(0);

                if(cursor->get_parent() == nullptr){//if there are no m_parent node(m_root case)
                    auto* new_parent = new BP_Node<T>(this->m_degree);
                    cursor->set_parent(new_parent);
                    new_node->set_parent(new_parent);

                    new_parent->set_item(0, prnt_item);
                    new_parent->inc_size();

                    new_parent->set_child(0,cursor);
                    new_parent->set_child(1,new_node);

                    m_root = new_parent;
                }
                else{//if there already have m_parent node
                    insert_prnt(cursor->get_parent(), new_node, prnt_item);
                }
            }
        }
    }

    void clear(BP_Node<T>* cursor){
        if(cursor != nullptr){
            if(!cursor->get_is_leaf()){
                for(int i=0; i <= cursor->get_size(); i++){
                    clear(cursor->get_child(i));
                }
            }
            delete[] cursor->get_itm_arr();
            delete[] cursor->get_chldrn_arr();
            delete cursor;
        }
    }
    void bpt_print(){
        std::cout <<"\n";
        print(m_root, 0);
    }
    void print(BP_Node<T>* cursor,int level) {
        // You must NOT edit this function.
        if (cursor != NULL) {
            for (int i = 0; i < cursor->get_size(); ++i) {
                    std::cout << cursor->get_item(i) << " ";

            }
            std::cout <<"level:"<<level++<< "\n";

            if (!cursor->get_is_leaf()) {
                for (int i = 0; i < cursor->get_size() + 1; ++i) {
                    print(cursor->get_child(i), level);
                }
            }
        }
    }
    std::vector<T> get_leaves_s(){
        return get_leaves(m_root);
    }
    std::vector<T> get_leaves(BP_Node<T>* cursor){
        std::vector<T> leaves;
        if (cursor != NULL) {
            for (int i = 0; i < cursor->get_size(); ++i) {
                if(cursor->get_is_leaf()){
                    leaves.push_back(cursor->get_item(i));
                }
            }
            if (!cursor->get_is_leaf()) {
                for (int i = 0; i < cursor->get_size() + 1; ++i) {
                    get_leaves(cursor->get_child(i));
                }
            }
        }
        return leaves;
    }

    int get_match_value_s(){
        std::vector<T> leafs;
        int value;
        value=get_match_value(m_root,leafs,value);
        return value;
    }
    int get_match_value(BP_Node<T>* cursor,std::vector<T> leafs,int value){
        std::string current;
        int aux;//TODO: borrar
        for(int i=0;i<leafs.size();i++){
            aux=0;
            current=leafs[i];
            std::cout<<"matching: "<<current;
            for(int j=0;j<leafs.size();j++){
                if(current==leafs[j]){
                    value++;
                    aux++;
                }
            }
            std::cout<<" found: "<<aux<<std::endl;
        }
        std::cout<<" final value: "<<value<<std::endl;
        return value;
    }
};