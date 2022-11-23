# pragma once
# include <map>
# include "../ADT/Tree.h"
# include "../ADT/Graph.h"
# include "../ADT/Digraph.h"

using std::map;

enum class Reset {
    NONE     = 0,
    PROCESS  = 1,
    VISITED  = 2,
    PREVIOUS = 3,
    MARKS    = 4,
    ALL      = 5
};

template<typename T>
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
void print_previous_set(VertexSet<T>* pSet) {
    auto iter = pSet->begin();
    auto end = pSet->end();
    printf("[");
    for (; iter != end; ++iter) {
        Vertex<T>* node = (*iter)->get_previous();
        if (node != nullptr) {
            printf(" V#%d ", node->get_key());
        } else {
            printf(" V#_ ");
        }
        
    } printf("]\n");
}

template<typename T>
inline void reset_node(Vertex<T>* pNode, Reset pFlag) {
    switch (pFlag) {
        case Reset::PROCESS:
            pNode->set_processed(false);
            break;
        case Reset::VISITED:
            pNode->set_visited(false);
            break;
        case Reset::PREVIOUS:
            pNode->set_previous(nullptr);
            break;
        case Reset::MARKS:
            pNode->set_processed(false);
            pNode->set_visited(false);
            break;
        case Reset::ALL:
            pNode->set_processed(false);
            pNode->set_visited(false);
            pNode->set_previous(nullptr);
        default:
            break;
    }
}

template<typename T>
void reset_nodes(iGraph<T>* pGraph, Reset pFlag = Reset::ALL) {
    if (pFlag != Reset::NONE) {
        for (int index = 0; index < pGraph->get_size(); ++index) {
            Vertex<T>* node = pGraph->get_vertex(index);
            reset_node(node, pFlag);
        }
    }
}

template<typename T>
void reset_nodes(VertexSet<T>* pSet, Reset pFlag = Reset::ALL) {
    if (pFlag != Reset::NONE) {
        for (int index = 0; index < pSet->size(); ++index) {
            Vertex<T>* node = pSet->at(index);
            reset_node(node, pFlag);
        }
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
bool are_sets_equal(VertexSet<T>* pSetA, VertexSet<T>* pSetB, Reset pFlag = Reset::ALL) {
    bool result = false;
    if (pSetA->size() == pSetB->size()) {
        process_nodes(pSetA);
        for (int index = 0; index < pSetB->size(); ++index) {
            Vertex<T>* node = pSetB->at(index);
            if (! node->is_processed()) {
                reset_nodes(pSetA, pFlag);
                return result;
            }
        } result = true;
        reset_nodes(pSetA, pFlag);
    } return result;
}

template<typename T>
void fast_intersect_sets(VertexSet<T>* pSetA, VertexSet<T>* pSetB, Reset pFlag = Reset::ALL) {
    process_nodes(pSetB);
    auto iter = pSetA->begin();
    while (iter != pSetA->end()) {
        Vertex<T>* node = *iter;
        if (! node->is_processed()) {
            iter = pSetA->erase(iter);
            continue;
        } ++iter;
    } reset_nodes(pSetB, pFlag);
}

template<typename T> // Avoids using node's mark data members
int count_intersection(VertexSet<T>* pSetA, VertexSet<T>* pSetB) {
    int count = 0;
    map<int, bool> processed_map;
    for (int index = 0; index < pSetA->size(); ++index) {
        int key = pSetA->at(index)->get_key();
        processed_map[key] = true;
    } for (int index = 0; index < pSetB->size(); ++index) {
        Vertex<T>* node = pSetB->at(index);
        if (! processed_map[node->get_key()]) {
            ++count;
        }
    } return count;
}

template<typename T>
bool compare_size(VertexSet<T>* pSetA, VertexSet<T>* pSetB) {
    int shared_size = count_intersection(pSetA, pSetB);
    int size_a = pSetA->size() - shared_size;
    int size_b = pSetB->size() - shared_size;
    return size_a > size_b;
}

template<typename T>
void fast_join_sets(VertexSet<T>* pSetA, VertexSet<T>* pSetB, Reset pFlag = Reset::ALL) {
    process_nodes(pSetA);
    for (int index = 0; index < pSetB->size(); ++index) {
        Vertex<T>* node = pSetB->at(index);
        if (! node->is_processed()) {
            pSetA->push_back(node);
        }
    } reset_nodes(pSetA, pFlag);
}

template<typename T>
VertexSet<T>* all_vertex_links(Vertex<T>* pNode) {
    VertexSet<T>* result = pNode->vertices_linked_to();
    VertexSet<T>* links_from = pNode->vertices_linked_from();
    auto iter = links_from->begin();
    while (iter != links_from->end()) {
        result->push_back(*iter);
        iter = links_from->erase(iter);
    } delete links_from;
    return result;
}