# pragma once
# include <map>
# include "iNode.h"
# include "NodeLink.h"

using std::map;

template<typename T>
class Vertex : public iNode<int,T> {
    typedef NodeLink<T> Link;

    private:
        bool processed;
        bool visited;
        Vertex<T>* previous;
        map<int, Link*>* link_list;
    
    public:
        Vertex(int pKey, T* pData = nullptr): iNode<int, T>(pKey, pData) {
            processed = visited = false;
            previous = nullptr;
            link_list = new map<int, Link*>;
        }

        ~Vertex() {
            clear_links();
            delete link_list;
        }

        map<int, Link*>* get_links() {
            return link_list;
        }

        Link* get_link(int pKey) {
            try {
                return link_list->at(pKey);
            } catch (const std::out_of_range& exception) {
                return nullptr;
            }
        }

        Link* get_link(Vertex<T>* pNode) {
            return get_link(pNode->get_key());
        }

        // Interfaz para adyacencias
        void join(Vertex<T>* pNode, int pWeight) {
            Link* link = new Link(this, pNode, pWeight);
            link_list->emplace(pNode->get_key(), link);
        }

        void detach(Vertex<T>* pNode) {
            detach(pNode->get_key());
        }

        void detach(int pKey) {
            Link* link = link_list->at(pKey);
            if (link != nullptr) {
                link_list->erase(pKey);
                delete link;
            }
        }

        void clear_links() {
            for (auto iter = link_list->begin(); iter != link_list->end(); ++iter) {
                Link* link = iter->second;
                delete link; // Elimina punteros del dato
            }
            link_list->clear(); // Vacia contenedor
        }

        bool is_joined(Vertex<T>* pNode) {
            return is_joined(pNode->get_key());
        }

        bool is_joined(int pKey) {
            return (link_list->find(pKey) != link_list->end());
        }

        // Interfaz para recorridos
        void set_previous(Vertex<T>* pPrev) {
            previous = pPrev;
        }

        void set_processed(bool pFlag) {
            processed = pFlag;
        }

        void set_visited(bool pFlag) {
            visited = pFlag;
        }
};