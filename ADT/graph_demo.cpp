# include <iostream>
# include "Digraph.h"
# include "Graph.h"

template<typename T>
void print_graph(iGraph<T>* pGraph) {
    auto vertices = pGraph->get_vertices();
    for (auto iter = vertices->begin(); iter != vertices->end(); ++iter) {
        int ID = iter->first;
        Vertex<T>* vertex = iter->second;
        auto links = vertex->get_links();
        printf("Vertex #%d: [", ID);
        for (auto it = links->begin(); it != links->end(); ++it) {
            ID = it->first;
            int weight = it->second->get_weight();
            printf("{#%d - W:%d}, ", ID, weight);
        }
        printf("]\n");
    }
}

template<typename T>
void graph_test(iGraph<T>* pGraph) {
    int size = pGraph->get_size();
    printf("-----------------------------------\n");
    printf("Graph Size: %d\n", size);
    print_graph(pGraph);

    auto vertices = pGraph->get_vertices();
    for (auto itrA = vertices->begin(); itrA != vertices->end(); ++itrA) {
        int keyA = itrA->first;
        auto links = itrA->second->get_links();
        printf("\nVertex #%d's Links:\n", keyA);

        for (auto itrB = links->begin(); itrB != links->end(); ++itrB) {
            int keyB = itrB->first;
            bool result = pGraph->are_linked(keyA, keyB);
            if (! result) {
                continue;
            }
            printf("Joined to #%d: %d\n", keyB, result);
        }
        printf("- end -\n");
    }
}

int main() {
    char data[] = {'A', 'B', 'C', 'D', 'E'};
    Graph<char>* graph = new Graph<char>;

    for (char c : data) {
        graph->insert_vertex(&c);
    }

    graph->join(1, 2, 1); // A-B
    graph->join(1, 3, 7); // A-C

    graph->join(2, 3, 5); // B-C
    graph->join(2, 4, 4); // B-D
    graph->join(2, 5, 3); // B-E

    graph->join(5, 3, 6); // D-E
    graph->join(5, 4, 2); // E-C
    /* Graph
           (A)
          /   \
        (B) - (C)
         |  \  |
        (D) - (E)
    */

    graph_test(graph);

    graph->join(1, 2, 10); // Update existing link's weight
    graph->join(5, 5, 16); // Add link to self
    graph->erase_vertex(2); // Erase vertex and links that point to it
    graph->erase_vertex(20); // Attempt to erase non-existing vertex
    graph_test(graph);

    delete graph;

    Digraph<char>* digraph = new Digraph<char>;
    for (char c : data) {
        digraph->insert_vertex(new char(c));
    }

    digraph->join(1, 2, 1); // A->B
    digraph->join(1, 5, 3); // A->E

    digraph->join(2, 3, 2); // B->C
    digraph->join(2, 4, 3); // B->D

    digraph->join(5, 4, 4); // E->D

    digraph->join(4, 2, 3); // D->B
    /* Digraph
        (A)  ---->  (B) -> (C)
         |           |
         --> (E) -> (D)
    */
    graph_test(digraph);

    digraph->join(3, 5, 7); // Add new directed link
    digraph->join(2, 3, 5); // Update existing link
    digraph->erase_vertex(4); // Erase existing vertex
    digraph->erase_vertex(10); // Erase non-existing vertex
    graph_test(digraph);

    return 0;
}