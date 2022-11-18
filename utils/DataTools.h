# pragma once
# include "../contentful/Registered.h"
# include "../ADT/Digraph.h"
# include "Date.h"

bool is_match_date(Vertex<Registered>* pNode, Date& pStart, Date& pEnd) {
    Registered* user= pNode->get_data();
    string postdate = user->getPostdate();
    Date user_date(postdate);
    return user_date.in_range(pStart, pEnd);
}

VertexSet<Registered>*  // Obtain matches in range of dates (inclusive)
matches_by_date(Vertex<Registered>* pNode, string& pStart, string& pEnd) {
    VertexSet<Registered>* matches = new VertexSet<Registered>;
    Date range_start(pStart);
    Date range_end(pEnd);
    for (int index = 0; index < pNode->link_quantity(); ++index) {
        NodeLink<Registered>* link = pNode->get_link(index);
        Vertex<Registered>* match = link->get_endpoint();
        if (is_match_date(match, range_start, range_end)) {
            matches->push_back(match);
        }
    }
    return matches;
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