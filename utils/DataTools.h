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

VertexSet<Registered>*  // Obtain matches in range of dates (inclusive)
matches_by_date(Vertex<Registered>* pNode, string& pStart, string& pEnd) {
    VertexSet<Registered>* all_matches = all_vertex_links(pNode);

    Date range_start(pStart), range_end(pEnd);
    auto iter = all_matches->begin();
    while (iter != all_matches->end()) {
        Vertex<Registered>* match = *iter;
        if (! is_match_date(match, range_start, range_end)) {
            iter = all_matches->erase(iter);
            continue;
        } ++iter;
    } return all_matches;
}