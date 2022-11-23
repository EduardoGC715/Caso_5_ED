# pragma once
# include <vector>
# include "iNode.h"
# include "NodeLink.h"

# define NOT_FOUND -1

using std::vector;

template<typename T>
using VertexSet = vector<Vertex<T>*>;

template<typename T>
using LinkSet = vector<NodeLink<T>*>;

template<typename T>
class Vertex : public iNode<int,T> {
    private:
        bool processed;
        bool visited;
        Vertex<T>* previous;
        VertexSet<T>* links_from;
        LinkSet<T>* links_to;

        int find_key(int pKey) {
            int stored_key;
            for (int index = 0; index < links_to->size(); ++index) {
                NodeLink<T>* stored_link = links_to->at(index);
                stored_key = stored_link->get_endpoint()->get_key();
                if (pKey == stored_key) {
                    return index;
                }
            } return NOT_FOUND;
        }

        int find_endpoint(Vertex<T>* pNode) {
            for (int index = 0; index < links_to->size(); ++index) {
                NodeLink<T>* stored_link = links_to->at(index);
                Vertex<T>* endpoint = stored_link->get_endpoint();
                if (pNode == endpoint) {
                    return index;
                }
            } return NOT_FOUND;
        }

        void erase_link_from(Vertex<T>* pNode) {
            auto iter = links_from->begin();
            while (iter != links_from->end()) {
                Vertex<T>* origin = *iter;
                if (pNode == origin) {
                    break;
                } ++iter;
            } links_from->erase(iter);
        }
    
    public:
        Vertex(int pKey, T* pData): iNode<int, T>(pKey, pData) {
            processed = visited = false;
            previous = nullptr;
            links_from = new VertexSet<T>;
            links_to = new LinkSet<T>;
        }

        ~Vertex() {
            clear_links();
            links_from->clear();
            delete links_to;
            delete links_from;
        }

        int link_quantity() {
            return links_to->size();
        }

        NodeLink<T>* find_link(int pKey) {
            int index = find_key(pKey);
            return get_link(index);
        }

        NodeLink<T>* find_link(Vertex<T>* pNode) {
            int index = find_endpoint(pNode);
            return get_link(index);
        }

        NodeLink<T>* get_link(int pIndex) {
            NodeLink<T>* result = nullptr;
            if (pIndex < link_quantity() && pIndex > NOT_FOUND) {
                result = links_to->at(pIndex);
            } 
            return result;
        }

        // Interfaz para adyacencias
        void join(Vertex<T>* pNode, int pWeight) {
            NodeLink<T>* link = new NodeLink<T>(this, pNode, pWeight);
            links_to->push_back(link);
            pNode->links_from->push_back(this);
        }

        void erase_link(int pIndex) {
            if (pIndex != NOT_FOUND) {
                NodeLink<T>* target = links_to->at(pIndex);
                Vertex<T>* endpoint = target->get_endpoint(); 
                links_to->erase(links_to->begin() + pIndex);
                endpoint->erase_link_from(this);
                delete target;
            }
        }

        VertexSet<T>* vertices_linked_from() {
            VertexSet<T>* set = new VertexSet<T>;
            for (int index = 0; index < links_from->size(); ++index) {
                Vertex<T>* node = links_from->at(index);
                set->push_back(node);
            } return set;
        }

        VertexSet<T>* vertices_linked_to() {
            VertexSet<T>* set = new VertexSet<T>;
            for (int index = 0; index < links_to->size(); ++index) {
                NodeLink<T>* link = links_to->at(index);
                Vertex<T>* node = link->get_endpoint();
                set->push_back(node);
            } return set;
        }

        void detach(Vertex<T>* pNode) {
            int index = find_endpoint(pNode);
            erase_link(index);
        }

        void detach(int pKey) {
            int index = find_key(pKey);
            erase_link(index);
        }

        void clear_links() {
            for (int index = 0; index < links_to->size(); ++index) {
                NodeLink<T>* link = links_to->at(index);
                delete link;
            }
            links_to->clear(); // Vacia contenedor
        }

        bool is_joined(Vertex<T>* pNode) {
            return (find_endpoint(pNode) != NOT_FOUND);
        }

        bool is_joined(int pKey) {
            return (find_key(pKey) != NOT_FOUND);
        }

        // Interfaz para recorridos
        Vertex<T>* get_previous() {
            return previous;
        }

        void set_previous(Vertex<T>* pPrev) {
            previous = pPrev;
        }

        bool is_processed() {
            return processed;
        }

        void set_processed(bool pFlag) {
            processed = pFlag;
        }

        bool is_visited() {
            return visited;
        }

        void set_visited(bool pFlag) {
            visited = pFlag;
        }
};