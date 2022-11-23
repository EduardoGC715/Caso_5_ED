# pragma once
# include <vector>
# include <stack>
# include <queue>
# include <map>
# include <iostream>
# include "GraphUtils.h"
# include "../ADT/Tree.h"
# include "../ADT/PriorityQueue.hpp"

using std::vector;
using std::stack;
using std::queue;
using std::map;
using std::pair;

template<typename T>
using SetCache = map<int, VertexSet<T>*>;

/*
||===========================||
||    Componentes Conexas    ||
||===========================||
*/

template<typename T>
VertexSet<T>* depth_search(iGraph<T>* pGraph, int pIndex = 0, Reset pFlag = Reset::NONE) {
    VertexSet<T>* visited_nodes = new VertexSet<T>;
    stack<Vertex<T>*> search_stack;

    Vertex<T>* current_node = pGraph->get_vertex(pIndex);
    search_stack.push(current_node);
    current_node->set_processed(true);
    while (! search_stack.empty()) {
        current_node = search_stack.top(); search_stack.pop();
        visited_nodes->push_back(current_node);
        current_node->set_visited(true);
        for (int index = 0; index < current_node->link_quantity(); ++index) {
            NodeLink<T>* link = current_node->get_link(index);
            Vertex<T>* endpoint = link->get_endpoint();
            if (! endpoint->is_processed()) {
                search_stack.push(endpoint);
                endpoint->set_previous(current_node);
                endpoint->set_processed(true);
            }
        }
    } reset_nodes(pGraph, pFlag);
    return visited_nodes;
}

template<typename T>
VertexSet<T>* depth_rsearch(iGraph<T>* pGraph, int pIndex = 0, Reset pFlag = Reset::NONE) {
    VertexSet<T>* visited_nodes = new VertexSet<T>;
    stack<Vertex<T>*> search_stack;

    Vertex<T>* current_node = pGraph->get_vertex(pIndex);
    search_stack.push(current_node);
    current_node->set_processed(true);
    while (! search_stack.empty()) {
        current_node = search_stack.top(); search_stack.pop();
        visited_nodes->push_back(current_node);
        current_node->set_visited(true);
        VertexSet<T>* links_from = current_node->vertices_linked_from();
        for (int index = 0; index < links_from->size(); ++index) {
            Vertex<T>* origin = links_from->at(index);
            if (! origin->is_processed() && pGraph->are_linked(origin, current_node)) {
                search_stack.push(origin);
                origin->set_processed(true);
            }
        }
    } reset_nodes(pGraph, pFlag);
    return visited_nodes;
}

template<typename T>
vector<VertexSet<T>*>* get_connected_sets(Digraph<T>* pGraph) {
    vector<VertexSet<T>*>* all_components = new vector<VertexSet<T>*>;
    map<int, bool> search_map;
    for (int search = 0; search < pGraph->get_size(); ++search) {
        if (! search_map[search]) {
            search_map[search] = true;
            VertexSet<T>* components = depth_search(pGraph, search, Reset::ALL); // aka descendants
            VertexSet<T>* ancestors = depth_rsearch(pGraph, search);
            fast_intersect_sets(components, ancestors);
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

/*
||==============================||
||    Cerraduras Transitivas    ||
||==============================||
*/

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
        for (int index = 0; index < endpoints->size(); ++index) {
            current_node = endpoints->at(index);
            if (! is_path_repeated(current_path, current_node))
            {// Insert path option AND enqueue to check its paths
                path_queue.push(path_tree->insert(current_node, current_path));
            } else { // Insert looped path as leaf
                path_tree->insert(current_node, current_path);
                current_node->set_processed(true); // For later use as ref.point
            }
        }
    } // print_path_tree(path_tree->get_root());
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
    /* for (int indexA = 0; indexA < loop_fullset->size(); ++indexA) {
        VertexSet<T>* loop_set = loop_fullset->at(indexA);
        printf("Set #%d: ", indexA);
        print_set(loop_set);
    } printf("\n"); */
    return loop_fullset;
}

/*
||==============================||
||       Cadenas de Valor       ||
||==============================||
*/

template<typename T>
VertexSet<T>* retrieve_vertex_set(SetCache<T>& pSetmap, Vertex<T>* pNode) {
    VertexSet<T>* result;
    if (pSetmap.count(pNode->get_key())) { // Retrieve if found
        result = pSetmap[pNode->get_key()];
    } else { // Create data otherwise
        pSetmap[pNode->get_key()] = result = all_vertex_links(pNode);
    } return result;
}

template<typename T>
int count_set_concurrency(SetCache<T>& pSetmap, Vertex<T>* pNode) {
    VertexSet<T>* node_set = retrieve_vertex_set(pSetmap, pNode);
    int count = node_set->size();
    return count;
}

template<typename T>
void load_concurrency(SetCache<T>& pSetmap, map<int,int>& pLog, Vertex<T>* pNode) {
    int key = pNode->get_key();
    pLog[key] = count_set_concurrency(pSetmap, pNode);
}

template<typename T>
void update_concurrency_sum(map<int,int>& pLog, map<int,int>& pCache, Vertex<T>* pNode) {
    int key = pNode->get_key();
    Vertex<T>* previous = pNode->get_previous();
    if (previous != nullptr && pCache[previous->get_key()])
    {// Use prev's sum to avoid iterative calculation
        pCache[key] = pLog[key] + pCache[previous->get_key()];
    } else {// If there's (no prev || no prev_sum), calculate
        Vertex<T>* current = pNode;
        while (current != nullptr) {
            pCache[key] += pLog[current->get_key()];
            current = current->get_previous();
        }
    }
}

template<typename T>
void clear_set_cache(SetCache<T>& pSetmap) {
    auto iter = pSetmap.begin();
    while (! pSetmap.empty()) {
        VertexSet<T>* set = iter->second;
        iter = pSetmap.erase(iter);
        delete set;
    }
}

template<typename T>
bool is_path_connected(Vertex<T>* pNodeA, Vertex<T>* pNodeB) {
    Vertex<T>* current = pNodeA;
    while (current != pNodeB && current != nullptr) {
        current = current->get_previous();
    } return (current == pNodeB);
}

template<typename T>
Vertex<T>* max_concurrency_chain(iGraph<T>* pGraph, Vertex<T>* pNode) {
    VertexSet<T>* visited_nodes = new VertexSet<T>;
    PriorityQueue<Vertex<T>> search_queue;
    map<int, int> concurrency_log, concurrency_sum;
    SetCache<T> all_edges;

    Vertex<T>* current_node = pNode;
    load_concurrency(all_edges, concurrency_log, current_node);
    search_queue.enqueue(current_node, 0);
    current_node->set_processed(true);
    while (! search_queue.isEmpty()) {
        current_node = search_queue.dequeue();
        current_node->set_visited(true);
        visited_nodes->push_back(current_node);
        for (int index = 0; index < current_node->link_quantity(); ++index) {
            NodeLink<T>* link = current_node->get_link(index);
            Vertex<T>* endpoint = link->get_endpoint();
            if (! endpoint->is_processed()) {
                int key = endpoint->get_key();
                endpoint->set_previous(current_node);
                endpoint->set_processed(true);
                load_concurrency(all_edges, concurrency_log, endpoint);
                search_queue.enqueue(endpoint, concurrency_log[key]);
            } else if (! is_path_connected(current_node, endpoint)) {
                endpoint->set_previous(current_node);
            }
        }
    } reset_nodes(visited_nodes, Reset::MARKS); // Unmark visited and processed flags
    clear_set_cache(all_edges);

    pair<int, Vertex<T>*> value_data(0, nullptr);
    for (int index = 0; index < visited_nodes->size(); ++index) {
        Vertex<T>* node = visited_nodes->at(index);
        update_concurrency_sum(concurrency_log, concurrency_sum, node);
        if (concurrency_sum[node->get_key()] >= value_data.first) {
            value_data.first = concurrency_sum[node->get_key()];
            value_data.second = node;
        }
    } delete visited_nodes;
    return value_data.second;
}

template<typename T>
double get_chain_size(Vertex<T>* pNode) {
    double count = 0;
    Vertex<T>* current = pNode;
    while (current != nullptr) {
        current = current->get_previous();
        ++count;
    } return count;
}

template<typename T>
Vertex<T>* min_concurrency_chain(iGraph<T>* pGraph, Vertex<T>* pNode) {
    VertexSet<T>* visited_nodes = new VertexSet<T>;
    queue<Vertex<T>*> search_queue;
    map<int, int> concurrency_log, concurrency_sum;
    SetCache<T> all_edges;

    Vertex<T>* current_node = pNode;
    load_concurrency(all_edges, concurrency_log, current_node);
    search_queue.push(current_node);
    current_node->set_processed(true);
    while (! search_queue.empty()) {
        current_node = search_queue.front(); search_queue.pop();
        current_node->set_visited(true);
        visited_nodes->push_back(current_node);
        for (int index = 0; index < current_node->link_quantity(); ++index) {
            NodeLink<T>* link = current_node->get_link(index);
            Vertex<T>* endpoint = link->get_endpoint();
            if (! endpoint->is_processed()) {
                endpoint->set_previous(current_node);
                endpoint->set_processed(true);
                search_queue.push(endpoint);
                load_concurrency(all_edges, concurrency_log, endpoint);
            }
        }
    } reset_nodes(visited_nodes, Reset::MARKS); // Unmark visited and processed flags
    clear_set_cache(all_edges);

    pair<double, Vertex<T>*> value_data(INT_MAX, pNode);
    for (int index = 1; index < visited_nodes->size(); ++index) {
        Vertex<T>* node = visited_nodes->at(index);
        update_concurrency_sum(concurrency_log, concurrency_sum, node);
        double rate = concurrency_sum[node->get_key()] / get_chain_size(node);
        if (rate <= value_data.first) {
            value_data.first = rate;
            value_data.second = node;
        }
    } delete visited_nodes;
    return value_data.second;
}