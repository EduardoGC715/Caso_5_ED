# pragma once
# include <vector>
# include "iNode.h"
# include "NodeLink.h"

# define NOT_FOUND -1

using std::vector;

template<typename T>
class Vertex : public iNode<int,T> {
    private:
        bool processed;
        bool visited;
        Vertex<T>* previous;
        vector<NodeLink<T>*>* link_list;

        int find_key(int pKey) {
            int stored_key;
            for (int index = 0; index < link_list->size(); ++index) {
                NodeLink<T>* stored_link = link_list->at(index);
                stored_key = stored_link->get_endpoint()->get_key();
                if (pKey == stored_key) {
                    return index;
                }
            } return NOT_FOUND;
        }

        int find_endpoint(Vertex<T>* pNode) {
            for (int index = 0; index < link_list->size(); ++index) {
                NodeLink<T>* stored_link = link_list->at(index);
                Vertex<T>* endpoint = stored_link->get_endpoint();
                if (pNode == endpoint) {
                    return index;
                }
            } return NOT_FOUND;
        }
    
    public:
        Vertex(int pKey, T* pData): iNode<int, T>(pKey, pData) {
            processed = visited = false;
            previous = nullptr;
            link_list = new vector<NodeLink<T>*>;
        }

        ~Vertex() {
            clear_links();
            delete link_list;
        }

        int link_quantity() {
            return link_list->size();
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
                result = link_list->at(pIndex);
            } 
            return result;
        }

        // Interfaz para adyacencias
        void join(Vertex<T>* pNode, int pWeight) {
            NodeLink<T>* link = new NodeLink<T>(this, pNode, pWeight);
            link_list->push_back(link);
        }

        void erase_link(int pIndex) {
            if (pIndex != NOT_FOUND) {
                NodeLink<T>* target = link_list->at(pIndex);
                link_list->erase(link_list->begin() + pIndex);
                delete target;
            }
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
            for (int index = 0; index < link_list->size(); ++index) {
                NodeLink<T>* link = link_list->at(index);
                delete link;
            }
            link_list->clear(); // Vacia contenedor
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