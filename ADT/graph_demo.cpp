# include <iostream>
# include <fstream>
# include <string>
# include "Digraph.h"
# include "Graph.h"

template<typename T>
void print_graph(iGraph<T>* pGraph) {
    for (int indexV = 0; indexV < pGraph->get_size(); ++indexV) {
        Vertex<T>* vertex = pGraph->get_vertex(indexV);
        printf("Vertex #%d: [", indexV+1);
        int link_size = vertex->link_quantity();
        for (int indexL = 0; indexL < link_size; ++indexL) {
            NodeLink<T>* link = vertex->get_link(indexL);
            int ID = link->get_endpoint()->get_key();
            int weight = link->get_weight();
            printf("{#%d - W:%d}, ", ID+1, weight);
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

    for (int indexA = 0; indexA < size; ++indexA) {
        Vertex<T>* vertex = pGraph->get_vertex(indexA);
        printf("\nVertex #%d's Links:\n", indexA+1);

        for (int indexB = 0; indexB < vertex->link_quantity(); ++indexB) {
            NodeLink<T>* link = vertex->get_link(indexB);
            int ID = link->get_endpoint()->get_key();
            printf("Joined to #%d\n", ID+1);
        }
        printf("- end -\n");
    }
}

template<typename T>
void output_graph(iGraph<T>* pGraph) {
    using namespace std;
    ofstream file("./Output/test_output.html");
    
    string line;
    ifstream temp("./templates/SankeyDiagram.txt");
    int i = 1;
    while (getline(temp, line) && i != 16) { // Primera parte del template
        file << line << "\n";
        ++i;
    }

    // Insertar datos nodos en formato ['{Origin Data}', '{Endpoint Data}', {weight}]
    string output;
    for (int indexA = 0; indexA < pGraph->get_size(); ++indexA) {
        Vertex<T>* origin_node = pGraph->get_vertex(indexA);
        T* origin_data = origin_node->get_data();
        origin_node->set_processed(true);
        
        for (int indexB = 0; indexB < origin_node->link_quantity(); ++indexB) {
            NodeLink<T>* link = origin_node->get_link(indexB);
            Vertex<T>* end_node = link->get_endpoint();
            if (end_node->is_processed()) {
                continue;
            }
            T* end_data = end_node->get_data();
            int weight = link->get_weight();
            output = "['" + to_string(*origin_data) + "', '" + to_string(*end_data) + "', " + to_string(weight) + "],\n";
            file << output;
        }
    }

    do { // Segunda parte del template
        file << line << "\n";
    } while (getline(temp, line));
    temp.close();
    file.close();
}

int main() {
    char data[] = {'A', 'B', 'C', 'D', 'E'};
    Graph<char>* graph = new Graph<char>;

    for (char c : data) {
        graph->insert_vertex(new char(c));
    }

    graph->join(0, 1, 1); // A-B
    graph->join(0, 2, 7); // A-C

    graph->join(1, 2, 5); // B-C
    graph->join(1, 3, 4); // B-D
    graph->join(1, 4, 3); // B-E

    graph->join(4, 2, 6); // D-E
    graph->join(4, 3, 2); // E-C
    /* Graph
           (A)
          /   \
        (B) - (C)
         |  \  |
        (D) - (E)
    */
    graph_test(graph);

    graph->join(0, 2, 10); // Update existing link's weight
    graph->join(4, 4, 16); // Add link to self
    graph->erase_vertex(1); // Erase vertex and links that point to it
    graph->erase_vertex(20); // Attempt to erase non-existing vertex
    graph_test(graph);

    Digraph<char>* digraph = new Digraph<char>;
    for (char c : data) {
        digraph->insert_vertex(new char(c));
    }

    digraph->join(0, 1, 1); // A->B
    digraph->join(0, 4, 3); // A->E

    digraph->join(1, 2, 2); // B->C
    digraph->join(1, 3, 3); // B->D

    digraph->join(4, 3, 4); // E->D

    digraph->join(3, 1, 3); // D->B
    /* Digraph
        (A)  ---->  (B) -> (C)
         |           |
         --> (E) -> (D)
    */
    graph_test(digraph);

    digraph->join(2, 4, 7); // Add new directed link
    digraph->join(1, 2, 5); // Update existing link
    digraph->erase_vertex(3); // Erase existing vertex
    digraph->erase_vertex(10); // Erase non-existing vertex
    graph_test(digraph);

    output_graph(graph);
    
    delete graph;
    delete digraph;
    return 0;
}