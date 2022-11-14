# pragma once
# include "iNode.h"

template<typename T>
class Vertex;

template<typename T>
class NodeLink {
    private:
        const int weight;
        Vertex<T>* origin;
        Vertex<T>* end;

    public:
        NodeLink(Vertex<T>* pOrigin, Vertex<T>* pEnd, int pWeight = 0)
        : origin(pOrigin), end(pEnd), weight(pWeight)
        {}

        Vertex<T>* get_origin() {
            return origin;
        }

        Vertex<T>* get_endpoint() {
            return end;
        }

        int get_weight() const {
            return weight;
        }
};