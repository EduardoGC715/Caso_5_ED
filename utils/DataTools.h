# pragma once
# include "../contentful/Registered.h"
# include "../ADT/Digraph.h"
# include "GraphTools.h"
# include "Date.h"

bool is_match_date(Vertex<Registered>* pNode, Date& pStart, Date& pEnd) {
    Registered* user= pNode->get_data();
    Date* postdate = user->getPostdate();
    return postdate->in_range(pStart, pEnd);
}

// TODO: Incluir links del grado entrada
VertexSet<Registered>*  // Obtain matches in range of dates (inclusive)
matches_by_date(Vertex<Registered>* pNode, string& pStart, string& pEnd) {
    Date range_start(pStart), range_end(pEnd);
    VertexSet<Registered>* all_matches = pNode->vertices_linked_to();
    join_sets(all_matches, pNode->vertices_linked_from());

    auto iter = all_matches->begin();
    while (iter != all_matches->end()) {
        Vertex<Registered>* match = *iter;
        if (! is_match_date(match, range_start, range_end)) {
            iter = all_matches->erase(iter);
            continue;
        } ++iter;
    } return all_matches;
}

// TODO: Componentes_conexas y su porcentaje -> HTML
// TODO: ioUtils + nickname_options()
/* Ejemplo

    Select a username:
        1. pablo_11
        2. carlos32__
        3. py_enjoyer
    Option: _

    Tras recibir option, pGraph.get_vertex( --option );
    Considerar validaciones
*/