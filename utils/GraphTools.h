# pragma once
# include <vector>
# include <stack>
# include <queue>
# include <iostream>
# include "../ADT/Tree.h"
# include "../ADT/Graph.h"
# include "../ADT/Digraph.h"

using std::stack;
using std::queue;

template<typename T>
void reset_nodes(iGraph<T>* pGraph) {
    for (int index = 0; index < pGraph->get_size(); ++index) {
        Vertex<T>* current = pGraph->get_vertex(index);
        current->set_previous(nullptr);
        current->set_processed(false);
        current->set_visited(false);
    }
}

template<typename T>
void reset_processed(iGraph<T>* pGraph) {
    for (int index = 0; index < pGraph->get_size(); ++index) {
        Vertex<T>* current = pGraph->get_vertex(index);
        current->set_processed(false);
    }
}

template<typename T>
Vertex<T>* find_unprocessed(iGraph<T>* pGraph) {
    Vertex<T>* result = nullptr;
    for (int index = 0; index < pGraph->get_size(); ++index) {
        Vertex<T>* current = pGraph->get_vertex(index);
        if (! current->is_processed()) {
            result = current;
            break;
        }
    }
    return result;
}

template<typename T>
int vertex_order_input(Digraph<T>* pGraph, Vertex<T>* pNode) {
    int count = 0;
    for (int index = 0; index < pGraph->get_size(); ++index) {
        Vertex<T>* current_node = pGraph->get_vertex(index);
        if (pGraph->are_linked(current_node, pNode)) {
            ++count;
        }
    }
    return count;
}

template<typename T>
VertexSet<T>* depth_search(iGraph<T>* pGraph, int pIndex = 0, bool pReset = false) {
    // printf("\nDescendant search (DFS)\n");
    VertexSet<T>* visited_nodes = new VertexSet<T>;
    stack<Vertex<T>*> search_stack;

    Vertex<T>* current_node = pGraph->get_vertex(pIndex);
    if (current_node != nullptr) {
        search_stack.push(current_node);
        current_node->set_processed(true);
        while (! search_stack.empty()) {
            current_node = search_stack.top();
            // printf("Visited V#%d\n", current_node->get_key());
            visited_nodes->push_back(current_node);
            current_node->set_visited(true);
            search_stack.pop();
            for (int index = 0; index < current_node->link_quantity(); ++index) {
                NodeLink<T>* link = current_node->get_link(index);
                Vertex<T>* endpoint = link->get_endpoint();
                if (! endpoint->is_processed()) {
                    search_stack.push(endpoint);
                    endpoint->set_previous(current_node);
                    endpoint->set_processed(true);
                    // printf("Processed V#%d\n", endpoint->get_key());
                }
            }
        }
    }
    if (pReset) {
        reset_nodes(pGraph);
    }
    return visited_nodes;
}

template<typename T>
VertexSet<T>* depth_rsearch(iGraph<T>* pGraph, int pIndex = 0, bool pReset = false) {
    // printf("\nAncestor search (reverse DFS)\n");
    VertexSet<T>* visited_nodes = new VertexSet<T>;
    stack<Vertex<T>*> search_stack;

    Vertex<T>* current_node = pGraph->get_vertex(pIndex);
    if (current_node != nullptr) {
        search_stack.push(current_node);
        current_node->set_processed(true);
        while (! search_stack.empty()) {
            current_node = search_stack.top();
            // printf("Visited V#%d\n", current_node->get_key());
            visited_nodes->push_back(current_node);
            current_node->set_visited(true);
            search_stack.pop();

            for (int index = 0; index < pGraph->get_size(); ++index) {
                Vertex<T>* origin = pGraph->get_vertex(index);
                if (! origin->is_processed() && pGraph->are_linked(origin, current_node)) {
                    search_stack.push(origin);
                    origin->set_processed(true);
                    // printf("Processed V#%d\n", origin->get_key());
                }
            }
        }
    }
    if (pReset) {
        reset_nodes(pGraph);
    }
    return visited_nodes;
}

template<typename T>
VertexSet<T>* common_endpoints(VertexSet<T>* pVertices, Vertex<T>* origin) {
    VertexSet<T>* endpoints = new VertexSet<T>;
    for (int index = 0; index < pVertices->size(); ++index) {
        Vertex<T>* current_node = pVertices->at(index);
        if (origin->is_joined(current_node)) {
            endpoints->push_back(current_node);
        }
    }
    return endpoints;
}

template<typename T>
vector<VertexSet<T>*>* connected_components(Digraph<T>* pGraph) {
    vector<VertexSet<T>*>* all_components = new vector<VertexSet<T>*>;
    bool search_list[pGraph->get_size()] = {};
    for (int search = 0; search < pGraph->get_size(); ++search) {
        if (! search_list[search]) {
            search_list[search] = true;
            VertexSet<T>* components = new VertexSet<T>;
            VertexSet<T>* descendants = depth_search(pGraph, search, true); // Resets nodes
            VertexSet<T>* ancestors = depth_rsearch(pGraph, search);
            for (int index = 0; index < descendants->size(); ++index)
            {// Interseccion viene de cuales nodos marco reverse_DFS en ancestors
                Vertex<T>* node = descendants->at(index);
                if (node->is_processed()) {
                    components->push_back(node);
                    search_list[node->get_key()] = true; // Descartar busqueda de comp.conexo
                }
            } all_components->push_back(components);
            delete descendants;
            delete ancestors;
            reset_nodes(pGraph);
        }
    }

    // Print de todas las componentes conexas
    for (int indexA = 0; indexA < all_components->size(); ++indexA) {
        printf("Components #%d: [", indexA);
        VertexSet<T>* components = all_components->at(indexA);
        for (int indexB = 0; indexB < components->size(); ++indexB) {
            Vertex<T>* node = components->at(indexB);
            printf(" V#%d", node->get_key());
        }
        printf("]\n");
    }printf("\n");
    return all_components;
}

template<typename T>
bool is_path_repeated(TreeNode<Vertex<T>>* pPath, Vertex<T>* pNode) {
    bool result = false;
    while (pPath != nullptr) {
        if (pNode == pPath->get_data()) {
            result = true;
            break;
        } pPath = pPath->get_parent();
    } return result;
}

template<typename T>
void cyclic_components(VertexSet<T>* pVertices) {
    typedef TreeNode<Vertex<T>> Path;
    queue< Path* > path_queue;
    Vertex<T>* current_node = pVertices->at(0);
    Tree<Vertex<T>>* path_tree = new Tree<Vertex<T>>(current_node);
    Path* current_path = path_tree->get_root();

    path_queue.push(current_path);

    while (! path_queue.empty()) {
        current_path = path_queue.front();
        path_queue.pop();
        current_node = current_path->get_data();
        printf("Dequeued V#%d\n", current_node->get_key());
        VertexSet<T>* endpoints = common_endpoints(pVertices, current_node);
        for (int index = 0; index < endpoints->size(); ++index) {
            current_node = endpoints->at(index);
            if (! is_path_repeated(current_path, current_node)) {
                printf("Enqueued V#%d\n", current_node->get_key());
                path_queue.push(path_tree->insert(current_node, current_path));
            } else {
                path_tree->insert(current_node, current_path);
                current_node->set_processed(true);
            }
        }
    }

    print_path_tree(path_tree->get_root());
}

template<typename T> // TODO: Borrar este metodo de prueba
void print_path_tree(TreeNode<Vertex<T>>* pPath, int pLevel = 0) {
    for (int index = 0; index < pLevel; ++index) {
        printf("    ");
    } ++pLevel;
    int key = pPath->get_data()->get_key();
    if (pPath->get_data()->is_processed()) {
        printf("Origin #%dX:\n", key);
    } else {
        printf("Vertex #%d:\n", key);
    }
    
    for (int index = 0; index < pPath->children_count(); ++index) {
        print_path_tree(pPath->get_child(index), pLevel);
    }
}