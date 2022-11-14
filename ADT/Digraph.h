# pragma once
# include "iGraph.h"

template<typename T>
class Digraph : iGraph<T> {
    public:
        Digraph() : iGraph<T>()
        {}

        void join(Vertex<T>* pNodeA, Vertex<T>* pNodeB, int pWeight = 0) {
            pNodeA->join(pNodeB, pWeight);
        }
        
        void join(int pIndexA, int pIndexB, int pWeight = 0) {
            Vertex<T>* node_A = get_vertex(pIndexA);
            Vertex<T>* node_B = get_vertex(pIndexB);
            join(node_A, node_B, pWeight);
        }

        void detach(Vertex<T>* pNodeA, Vertex<T>* pNodeB) {
            pNodeA->detach(pNodeB);
        }

        void detach(int pIndexA, int pIndexB) {
            Vertex<T>* node_A = get_vertex(pIndexA);
            Vertex<T>* node_B = get_vertex(pIndexB);
            detach(node_A, node_B);
        }
};