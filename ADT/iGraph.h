# pragma once
# include <iostream>
# include "Vertex.h"

template<typename T>
class iGraph {
    private:
        vector<Vertex<T>*>* vertices;

    public:
        iGraph() {
            vertices = new vector<Vertex<T>*>;
        }

        ~iGraph() {
            clear();
            delete vertices;
        }

        Vertex<T>* get_vertex(int pIndex) {
            try {
                return vertices->at(pIndex);
            } catch (const std::out_of_range& exception) {
                return nullptr;
            }
        }

        int get_size() const {
            return vertices->size();
        }

        void insert_vertex(T* pData) {
            int ID = get_size();
            Vertex<T>* node = new Vertex<T>(ID, pData);
            vertices->push_back(node);
        }

        T* erase_vertex(int pIndex) {
            T* data = nullptr;
            Vertex<T>* target = get_vertex(pIndex);
            if (target != nullptr) {
                vertices->erase(vertices->begin() + pIndex);
                for (int index = 0; index < get_size(); ++index) {
                    Vertex<T>* node = get_vertex(index);
                    if (are_linked(node, target)) {
                        detach(node, target);
                    }
                    if (index >= pIndex) { // Update keys to match index
                        int stored_key = node->get_key();
                        node->set_key(--stored_key);
                    }
                }
                data = target->get_data();
                delete target;
            }
            return data;
        }

        void clear() {
            for (int index = 0; index < get_size(); ++index) {
                Vertex<T>* node = get_vertex(index);
                delete node;
            }
            vertices->clear();
        }

        bool are_linked(int pIndexA, int pIndexB) {
            bool result = false;
            Vertex<T>* node_A = get_vertex(pIndexA);
            if (node_A != nullptr) {
                result = node_A->is_joined(pIndexB);
            }
            return result;
        }

        bool are_linked(Vertex<T>* pNodeA, Vertex<T>* pNodeB) {
            return pNodeA->is_joined(pNodeB);
        }

        virtual void join(Vertex<T>*, Vertex<T>*, int) = 0;
        virtual void join(int, int, int) = 0;

        virtual void detach(int, int) = 0;
        virtual void detach(Vertex<T>*, Vertex<T>*) = 0;
};