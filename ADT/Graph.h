# pragma once
# include "iGraph.h"

template<typename T>
class Graph : public iGraph<T> {
    public:
        Graph() : iGraph<T>()
        {}

        void join(Vertex<T>* pNodeA, Vertex<T>* pNodeB, int pWeight = 0) {
            bool looped = (pNodeA == pNodeB);
            if (! this->are_linked(pNodeA, pNodeB)) {
                pNodeA->join(pNodeB, pWeight);
                if (! looped) {
                    pNodeB->join(pNodeA, pWeight);
                }
            } else { // Update if already linked
                pNodeA->get_link(pNodeB)->set_weight(pWeight);
                if (! looped) {
                    pNodeB->get_link(pNodeA)->set_weight(pWeight);
                }
            }
        }
        
        void join(int pIndexA, int pIndexB, int pWeight = 0) {
            Vertex<T>* node_A = this->get_vertex(pIndexA);
            Vertex<T>* node_B = this->get_vertex(pIndexB);
            if (node_A != nullptr && node_B != nullptr) {
                join(node_A, node_B, pWeight);
            }
        }

        void detach(Vertex<T>* pNodeA, Vertex<T>* pNodeB) {
            if (pNodeA != pNodeB) {
                pNodeA->detach(pNodeB);
                pNodeB->detach(pNodeA);
            } else {
                pNodeA->detach(pNodeB);
            }
        }

        void detach(int pIndexA, int pIndexB) {
            Vertex<T>* node_A = this->get_vertex(pIndexA);
            Vertex<T>* node_B = this->get_vertex(pIndexB);
            if (node_A != nullptr && node_B != nullptr) {
                detach(node_A, node_B);
            }
        }
};