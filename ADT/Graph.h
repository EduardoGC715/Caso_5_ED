# pragma once
# include "iGraph.h"

template<typename T>
class Graph : iGraph<T> {
    public:
        Graph() : iGraph<T>()
        {}

        void join(Vertex<T>* pNodeA, Vertex<T>* pNodeB, int pWeight = 0) {
            pNodeA->join(pNodeB, pWeight);
            pNodeB->join(pNodeA, pWeight);
        }
        
        void join(int pIndexA, int pIndexB, int pWeight = 0) {
            Vertex<T>* node_A = get_vertex(pIndexA);
            Vertex<T>* node_B = get_vertex(pIndexB);
            join(node_A, node_B, pWeight);
        }

        void detach(Vertex<T>* pNodeA, Vertex<T>* pNodeB) {
            pNodeA->detach(pNodeB);
            pNodeB->detach(pNodeA);
        }

        void detach(int pIndexA, int pIndexB) {
            Vertex<T>* node_A = get_vertex(pIndexA);
            Vertex<T>* node_B = get_vertex(pIndexB);
            detach(node_A, node_B);
        }
};