# pragma once
# include <iostream>
# include "Vertex.h"

template<typename T>
class iGraph {
    private:
        int queued_ID = 0;
        map<int, Vertex<T>*>* node_list;

    public:
        iGraph() : node_list()
        {}

        ~iGraph() {
            clear();
            delete node_list;
        }

        map<int, Vertex<T>*>* get_vertices() {
            return node_list;
        }

        Vertex<T>* get_vertex(int pIndex) {
            return node_list->at(pIndex);
        }

        int get_size() const {
            return node_list->size();
        }

        void insert_vertex(T* pData) {
            Vertex<T>* node = new Vertex<T>(queued_ID, pData);
            node_list->emplace(queued_ID++, node);
        }

        T* erase_vertex(int pIndex) {
            Vertex<T>* node = get_vertex(pIndex);
            node_list->erase(nodes->begin() + pIndex);
            T* data = node->get_data();
            delete node;
            return data;
        }

        void clear() {
            for (auto iter : node_list) { // Elimina nodos individuales
                delete iter->first;
            }
            node_list->clear();
        }

        bool are_linked(int pIndexA, int pIndexB) {
            Vertex<T>* node_A = get_vertex(pIndexA);
            return node_A->is_joined(pIndexB);
        }

        bool are_linked(Vertex<T>* pNodeA, Vertex<T>* pNodeB) {
            return pNodeA->is_joined(pNodeB)
        }

        virtual void join(Vertex<T>*, Vertex<T>*, int) = 0;
        virtual void join(int, int, int) = 0;

        virtual void detach(int, int) = 0;
        virtual void detach(Vertex<T>*, Vertex<T>*) = 0;
};