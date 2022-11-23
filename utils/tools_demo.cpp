# include "GraphTools.h"
# include <string>

using namespace std;

int main() {
    vector<VertexSet<string>*>* connected_comps;
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

    // delete cyclic_components(graph_1);

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

    // delete cyclic_components(graph_2);

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

    // delete cyclic_components(graph_3);

    Digraph<string>* graph_4 = new Digraph<string>;
    string data_4[] = {"A", "B", "C", "D", "E", "F", "G", "H"};
    for (int index = 0; index < 8; ++index) {
        graph_4->insert_vertex(data_4 + index);
    }

    // A0, B1, C2, D3, E4, F5, XG6, H7
    graph_4->join(0, 1); // A->B
    graph_4->join(0, 4); // A->E
    graph_4->join(0, 6); // A->G

    graph_4->join(1, 3); // B->D

    graph_4->join(2, 4); // C->E
    graph_4->join(2, 3); // C->D
    graph_4->join(2, 0); // C->A

    graph_4->join(3, 5); // D->F
    graph_4->join(3, 7); // D->H
    graph_4->join(3, 2); // D->C

    graph_4->join(4, 0); // E->A
    graph_4->join(7, 2); // H->C

    // delete cyclic_components(graph_4);
    delete get_connected_sets(graph_4);

    Digraph<string>* graph_5 = new Digraph<string>;
    string data_5[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O"};
    for (int index = 0; index < 15; ++index) {
        graph_5->insert_vertex(data_5 + index);
    }

    graph_5->join(0, 1); // A -> B
    graph_5->join(0, 4); // A -> E
    graph_5->join(0, 8); // A -> I

    graph_5->join(1, 2); // B -> C
    graph_5->join(2, 3); // C -> D

    graph_5->join(3, 12); // D -> M
    graph_5->join(3, 13); // D -> N
    graph_5->join(3, 14); // D -> O

    graph_5->join(4, 5); // E -> F
    graph_5->join(4, 6); // E -> G
    graph_5->join(4, 7); // E -> H

    graph_5->join(5, 1); // F -> B
    graph_5->join(5, 6); // F -> G

    graph_5->join(6, 5); // G -> F
    graph_5->join(7, 5); // H -> F

    graph_5->join(8, 9); // I -> J
    graph_5->join(8, 10); // I -> K
    graph_5->join(8, 11); // I -> L

    graph_5->join(14, 12); // O -> M
    graph_5->join(14, 13); // O -> N


    // max_concurrency_chain(graph_5, graph_5->get_vertex(0));
    // min_concurrency_chain(graph_5, graph_5->get_vertex(0));
    return 0;
}