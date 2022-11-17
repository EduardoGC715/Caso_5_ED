# include "GraphTools.h"
# include <string>

using namespace std;

int main() {
    Digraph<string>* graph_1 = new Digraph<string>;
    string data_1[] = {"A", "B", "C", "D", "E"};
    for (int index = 0; index < 5; ++index) {
        graph_1->insert_vertex(data_1 + index);
    }

    graph_1->join(0, 1); // A->B
    graph_1->join(0, 3); // A->D

    graph_1->join(1, 3); // B->D

    graph_1->join(2, 1); // C->B

    graph_1->join(3, 2); // D->C
    graph_1->join(3, 4); // D->E

    graph_1->join(4, 2); // E->C

    delete connected_components<string>(graph_1);

    Digraph<string>* graph_2 = new Digraph<string>;
    string data_2[] = {"A", "B", "C", "D", "E", "F", "G", "H"};
    for (int index = 0; index < 8; ++index) {
        graph_2->insert_vertex(data_2 + index);
    }

    graph_2->join(0, 3); // A->D

    graph_2->join(1, 0); // B->A

    graph_2->join(2, 0); // C->A
    graph_2->join(2, 6); // C->G

    graph_2->join(3, 6); // D->G

    graph_2->join(4, 5); // E->F
    graph_2->join(4, 7); // E->H

    graph_2->join(5, 4); // F->E
    graph_2->join(5, 7); // F->H

    graph_2->join(6, 2); // G->C

    graph_2->join(7, 4); // H->E
    graph_2->join(7, 5); // H->F

    delete connected_components<string>(graph_2);

    Digraph<string>* graph_3 = new Digraph<string>;
    string data_3[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K"};
    for (int index = 0; index < 11; ++index) {
        graph_3->insert_vertex(data_3 + index);
    }

    graph_3->join(0, 1); // A->B
    graph_3->join(0, 2); // A->C
    graph_3->join(1, 3); // B->D
    graph_3->join(2, 4); // C->E
    graph_3->join(3, 7); // D->H
    graph_3->join(3, 5); // D->F
    graph_3->join(4, 5); // E->F
    // graph_3->join(4, 6); // E->G
    graph_3->join(5, 10); // F->K
    graph_3->join(6, 9); // G->J
    graph_3->join(7, 8); // H->I
    graph_3->join(8, 0); // I->A
    graph_3->join(9, 0); // J->A
    graph_3->join(10, 4); // K->E

    delete connected_components(graph_3);
    return 0;
}