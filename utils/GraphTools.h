# pragma once
# include <vector>
# include <stack>
# include <queue>
# include <map>
# include <iostream>
# include "../ADT/Tree.h"
# include "../ADT/Graph.h"
# include "../ADT/Digraph.h"

using std::vector;
using std::stack;
using std::queue;
using std::map;

template<typename T>
void print_set(VertexSet<T>* pSet) {
    auto iter = pSet->begin();
    auto end = pSet->end();
    printf("[");
    for (; iter != end; ++iter) {
        Vertex<T>* node = *iter;
        printf(" V#%d ", node->get_key());
    } printf("]\n");
}

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
void reset_nodes(VertexSet<T>* pSet) {
    for (int index = 0; index < pSet->size(); ++index) {
        Vertex<T>* current = pSet->at(index);
        current->set_previous(nullptr);
        current->set_processed(false);
        current->set_visited(false);
    }
}

template<typename T>
void process_nodes(VertexSet<T>* pSet) {
    for (int index = 0; index < pSet->size(); ++index) {
        Vertex<T>* current = pSet->at(index);
        current->set_processed(true);
    }
}

template<typename T>
bool are_sets_equal(VertexSet<T>* pSetA, VertexSet<T>* pSetB) {
    bool result = false;
    if (pSetA->size() == pSetB->size()) {
        process_nodes(pSetA);
        for (int index = 0; index < pSetB->size(); ++index) {
            Vertex<T>* node = pSetB->at(index);
            if (! node->is_processed()) {
                reset_nodes(pSetA);
                return result;
            }
        } result = true;
        reset_nodes(pSetA);
    } return result;
}

template<typename T>
void intersect_sets(VertexSet<T>* pSetA, VertexSet<T>* pSetB) {
    process_nodes(pSetB);
    auto iter = pSetA->begin();
    while (iter != pSetA->end()) {
        Vertex<T>* node = *iter;
        if (! node->is_processed()) {
            iter = pSetA->erase(iter);
            continue;
        } ++iter;
    } reset_nodes(pSetB);
}

template<typename T>
void join_sets(VertexSet<T>* pSetA, VertexSet<T>* pSetB) {
    process_nodes(pSetA);
    for (int index = 0; index < pSetB->size(); ++index) {
        Vertex<T>* node = pSetB->at(index);
        if (! node->is_processed()) {
            pSetA->push_back(node);
        }
    } reset_nodes(pSetA);
}

template<typename T>
VertexSet<T>* all_vertex_links(Digraph<T>* pGraph, Vertex<T>* pNode) {
    VertexSet<T>* result = vertex_order_in(pGraph, pNode);
    VertexSet<T>* order_out = vertex_order_out(pNode);
    join_sets(result, order_out);
    delete order_out;
    return result;
}

template<typename T>
VertexSet<T>* depth_search(iGraph<T>* pGraph, int pIndex = 0) {
    // printf("\nDescendant search (DFS)\n");
    VertexSet<T>* visited_nodes = new VertexSet<T>;
    stack<Vertex<T>*> search_stack;

    Vertex<T>* current_node = pGraph->get_vertex(pIndex);
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
    return visited_nodes;
}

template<typename T>
VertexSet<T>* depth_rsearch(iGraph<T>* pGraph, int pIndex = 0) {
    // printf("\nAncestor search (reverse DFS)\n");
    VertexSet<T>* visited_nodes = new VertexSet<T>;
    stack<Vertex<T>*> search_stack;

    Vertex<T>* current_node = pGraph->get_vertex(pIndex);
    search_stack.push(current_node);
    current_node->set_processed(true);
    while (! search_stack.empty()) {
        current_node = search_stack.top();
        // printf("Visited V#%d\n", current_node->get_key());
        visited_nodes->push_back(current_node);
        current_node->set_visited(true);
        search_stack.pop();

        VertexSet<T>* links_from = current_node->vertices_linked_from();
        for (int index = 0; index < links_from->size(); ++index) {
            Vertex<T>* origin = links_from->at(index);
            if (! origin->is_processed() && pGraph->are_linked(origin, current_node)) {
                search_stack.push(origin);
                origin->set_processed(true);
                // printf("Processed V#%d\n", origin->get_key());
            }
        }
    }
    return visited_nodes;
}

template<typename T> // Finds all of origin's endpoints available in a set
VertexSet<T>* common_endpoints(VertexSet<T>* pSet, Vertex<T>* origin) {
    VertexSet<T>* endpoints = new VertexSet<T>;
    for (int index = 0; index < pSet->size(); ++index) {
        Vertex<T>* current_node = pSet->at(index);
        if (origin->is_joined(current_node)) {
            endpoints->push_back(current_node);
        }
    } return endpoints;
}

template<typename T>
vector<VertexSet<T>*>* get_connected_sets(Digraph<T>* pGraph) {
    vector<VertexSet<T>*>* all_components = new vector<VertexSet<T>*>;
    map<int, bool> search_map;
    for (int search = 0; search < pGraph->get_size(); ++search) {
        if (! search_map[search]) {
            search_map[search] = true;
            VertexSet<T>* components = depth_search(pGraph, search); // aka descendants
            reset_nodes(components);
            VertexSet<T>* ancestors = depth_rsearch(pGraph, search);
            intersect_sets(components, ancestors);
            for (int index = 0; index < components->size(); ++index) {
                Vertex<T>* node = components->at(index);
                search_map[node->get_key()] = true; // Descartar busqueda de comp.conexo
            } delete ancestors;
            all_components->push_back(components);
        }
    }

    // Print de todas las componentes conexas
    /* for (int indexA = 0; indexA < all_components->size(); ++indexA) {
        VertexSet<T>* components = all_components->at(indexA);
        printf("Components #%d: ", indexA);
        print_set(components);
    } printf("\n"); */
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
Tree<Vertex<T>>* get_set_map(VertexSet<T>* pSet) {
    typedef TreeNode<Vertex<T>> Path;
    Tree<Vertex<T>>* path_tree; // Path tree to map all routes
    queue< Path* > path_queue; // Queue for current path mapping
    Vertex<T>* current_node;
    Path* current_path;

    // Init required conditions
    current_node = pSet->at(0);
    path_tree = new Tree<Vertex<T>>(current_node);
    current_path = path_tree->get_root();
    path_queue.push(current_path);

    while (! path_queue.empty())
    { // BFS-like design to exhaust all potential paths
        current_path = path_queue.front();
        path_queue.pop();
        current_node = current_path->get_data();
        VertexSet<T>* endpoints = common_endpoints(pSet, current_node);
        // printf("Dequeued V#%d\n", current_node->get_key());
        for (int index = 0; index < endpoints->size(); ++index) {
            current_node = endpoints->at(index);
            if (! is_path_repeated(current_path, current_node))
            {// Insert path option AND enqueue to check its paths
                // printf("Enqueued V#%d\n", current_node->get_key());
                path_queue.push(path_tree->insert(current_node, current_path));
            } else { // Insert looped path as leaf
                path_tree->insert(current_node, current_path);
                current_node->set_processed(true); // For later use as ref.point
            }
        }
    }

    // print_path_tree(path_tree->get_root());
    return path_tree;
}

template<typename T>
void get_all_loops(VertexSet<T>* pVertices, vector<VertexSet<T>*>* pFullset) {
    typedef TreeNode<Vertex<T>> Path;
    Tree<Vertex<T>>* path_map = get_set_map(pVertices);

    for (int index = 0; index < pVertices->size(); ++index) {
        Vertex<T>* current_node = pVertices->at(index);
        if (! current_node->is_processed()) {
            continue;
        }// Else, use marked node as reference point for loops
        queue<Path*>* ref_points = path_map->find_all(current_node);
        Path* root_path = ref_points->front();
        Path* end_path;

        ref_points->pop();
        while (! ref_points->empty()) {// Obtain all loops from root's data
            VertexSet<T>* loop_set = new VertexSet<T>;
            end_path = ref_points->front();
            ref_points->pop();
            while (end_path != root_path && end_path != nullptr)
            {// Retrace path from end_path to root_path
                loop_set->emplace(loop_set->begin(), end_path->get_data());
                end_path = end_path->get_parent();
            } if (end_path != nullptr && loop_set->size() > 2) {
                pFullset->push_back(loop_set);
            } else {// no link from end to root in branch || loop too small
                delete loop_set;
            }
        } delete ref_points;
    } delete path_map;
}

template<typename T>
void sanitize_loop_sets(vector<VertexSet<T>*>* pFullset, int pStart) {
    auto position = pFullset->begin() + pStart;
    auto next = position + 1;
    while (position != pFullset->end()) {
        VertexSet<T>* set_reference = *position;
        for (auto iter = position+1; iter != pFullset->end();) {
            VertexSet<T>* current_set = *iter;
            if (are_sets_equal(set_reference, current_set)) {
                iter = pFullset->erase(iter);
            } else {
                ++iter;
            }
        } ++position;
    }
}

template<typename T>
vector<VertexSet<T>*>* cyclic_components(Digraph<T>* pGraph) {
    vector<VertexSet<T>*>* loop_fullset = new vector<VertexSet<T>*>;
    vector<VertexSet<T>*>* connected_sets = get_connected_sets(pGraph);

    int index_queue = 0;
    for (int index = 0; index < connected_sets->size(); ++index) {
        VertexSet<T>* stored_set = connected_sets->at(index);
        if (stored_set->size() > 2) {
            get_all_loops(stored_set, loop_fullset);
            reset_nodes(stored_set);
            sanitize_loop_sets(loop_fullset, index_queue);
            index_queue = loop_fullset->size();
        } else {
            delete stored_set;
            continue;
        }
    }

    // Print de todas las componentes ciclicas
    for (int indexA = 0; indexA < loop_fullset->size(); ++indexA) {
        VertexSet<T>* loop_set = loop_fullset->at(indexA);
        printf("Set #%d: ", indexA);
        print_set(loop_set);
    } printf("\n");
    return loop_fullset;
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
    
    for (int index = 0; index < pPath->child_count(); ++index) {
        print_path_tree(pPath->get_child(index), pLevel);
    }
}

template<typename T>
VertexSet<T>* get_longest_chain(Digraph<T>* pGraph, Vertex<T>* pNode) {

}