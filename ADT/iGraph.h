# pragma once
# include <iostream>
# include "Vertex.h"

template<typename T>
class iGraph {
    private:
        int queued_ID = 1;
        map<int, Vertex<T>*>* vertices;

    public:
        iGraph() {
            vertices = new map<int, Vertex<T>*>;
        }

        ~iGraph() {
            clear();
            delete vertices;
        }

        map<int, Vertex<T>*>* get_vertices() {
            return vertices;
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
            Vertex<T>* node = new Vertex<T>(queued_ID, pData);
            vertices->emplace(queued_ID, node);
            ++queued_ID;
        }

        T* erase_vertex(int pIndex) {
            T* data = nullptr;
            Vertex<T>* target = get_vertex(pIndex);
            if (target != nullptr) {
                vertices->erase(pIndex);
                for (auto iter = vertices->begin(); iter != vertices->end(); ++iter)
                {// Eliminar arcos que lleguen al vertice objetivo
                    Vertex<T>* vertex = iter->second;
                    if (are_linked(vertex, target)) {
                        detach(vertex, target);
                    }
                }
                data = target->get_data();
                delete target;
            }
            return data;
        }

        void clear() {
            for (auto iter = vertices->begin(); iter != vertices->end(); ++iter) {
                Vertex<T>* vertex = iter->second;
                delete vertex; // Elimina nodos individuales
            }
            vertices->clear();
        }

        bool are_linked(int pIndexA, int pIndexB) {
            Vertex<T>* node_A = get_vertex(pIndexA);
            if (node_A != nullptr) {
                return node_A->is_joined(pIndexB);
            } else {
                return false;
            }
        }

        bool are_linked(Vertex<T>* pNodeA, Vertex<T>* pNodeB) {
            return pNodeA->is_joined(pNodeB);
        }

        virtual void join(Vertex<T>*, Vertex<T>*, int) = 0;
        virtual void join(int, int, int) = 0;

        virtual void detach(int, int) = 0;
        virtual void detach(Vertex<T>*, Vertex<T>*) = 0;
};