#pragma once
#include <iostream>
#include <fstream>
#include <windows.h>
#include "../contentful/Registered.h"
#include "../utils/GraphTools.h"
#include "../utils/DataTools.h"

using std::pair;
using std::ofstream;
using std::ifstream;

/*
||=================================||
||           HTML  Utils           ||
||=================================||
*/

void show_html(string& pPath){
    ShellExecute(nullptr, "open", pPath.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
}

string parse_user(Vertex<Registered>* pNode, int pColor) {
    string html_node = "            ";
    Registered* user = pNode->get_data();
    html_node.append( "{ name: \"" + user->getNickname() 
        + "\", offer: \"" + user->getOffer()
        + "\", demand: \"" + user->getDemand()
        + "\", postdate: \"" + *(user->getPostdate()->to_string())
        + "\", colorID: \"" + to_string(pColor)
        + "\"},\n");
    return html_node;
}

string parse_link(NodeLink<Registered>* pLink) {
    Vertex<Registered>* origin = pLink->get_origin();
    Vertex<Registered>* endpoint = pLink->get_endpoint();
    string html_link = "            ";
    html_link.append( "{ source: \"" + origin->get_data()->getNickname()
        + "\", target: \"" + endpoint->get_data()->getNickname()
        + "\", weight: \"" + to_string(pLink->get_weight())
        + "\"},\n");
    return html_link;
}

string parse_colors(vector<string>& pColors) {
    string html_colors = "        ";
    for (auto iter = pColors.begin(); iter != pColors.end();) {
        string color = "\"" + *iter + "\", ";
        html_colors.append(color);
        ++iter;
    } return html_colors;
}

void build_html_graph(vector<string>& pColors, pair<string, string>* pData) {
    string colors = parse_colors(pColors);
    ofstream file_output;
    ifstream file_template;
    string path = "Output\\index.html";
    file_output.open(path, ostream::out | ofstream::trunc);
    file_template.open("templates\\html_template.txt");

    string line;
    int line_num = 1;
    while (getline(file_template, line) && line_num != 21) {
        file_output << line << "\n";
        ++line_num;
    }
    file_output << pData->first; // Inserts node data
    while (getline(file_template, line) && line_num != 23) {
        file_output << line << "\n";
        ++line_num;
    }
    file_output << pData->second; // Inserts link data
    while (getline(file_template, line) && line_num != 70) {
        file_output << line << "\n";
        ++line_num;
    } file_output << colors << "\n";
    
    while (getline(file_template, line)) {
        file_output << line << "\n";
    } file_template.close();
    file_output.close();
    delete pData;
}

/*
||=================================||
||         Grafo  Completo         ||
||=================================||
*/

pair<string, string>* parse_graph(Digraph<Registered>* pGraph, int pColorsize) {
    pair<string, string>* graph_data = new pair<string,string>;
    for (int index_a = 0; index_a < pGraph->get_size(); ++index_a) {
        Vertex<Registered>* current = pGraph->get_vertex(index_a);
        int color_id = random(0, pColorsize);
        graph_data->first.append(parse_user(current, color_id));
        for (int index_b = 0; index_b < current->link_quantity();) {
            NodeLink<Registered>* link = current->get_link(index_b);
            graph_data->second.append(parse_link(link));
            ++index_b;
        }
    } return graph_data;
}

void output_graph(Digraph<Registered>* pGraph) {
    vector<string> colors = {"#66c2a5","#fc8d62","#8da0cb","#e78ac3","#a6d854","#ffd92f","#e5c494","#b3b3b3"};
    build_html_graph(colors, parse_graph(pGraph, colors.size()-1));
}

/*
||=================================||
||       Componentes Conexas       ||
||=================================||
*/

void parse_connected_set(pair<string, string>* pData, VertexSet<Registered>* pSet, int pColor) {
    process_nodes(pSet);
    for (auto iter = pSet->begin(); iter != pSet->end();) {
        Vertex<Registered>* node = *iter;
        pData->first.append(parse_user(node, pColor));
        for (int index = 0; index < node->link_quantity();) {
            NodeLink<Registered>* link = node->get_link(index);
            Vertex<Registered>* target = link->get_endpoint();
            if (target->is_processed()) {
                pData->second.append(parse_link(link));
            } ++index;
        } ++iter;
    } reset_nodes(pSet);
}

void output_connected_sets(Digraph<Registered>* pGraph) {
    vector<string> colors = {"#4e79a7","#f28e2c","#e15759","#76b7b2","#59a14f","#edc949","#af7aa1","#ff9da7","#9c755f","#bab0ab"};
    vector<VertexSet<Registered>*>* all_sets = get_connected_sets(pGraph);
    pair<string, string>* graph_data = new pair<string, string>;
    for (auto iter = all_sets->begin(); iter != all_sets->end();) {
        VertexSet<Registered>* set = *iter;
        int color_id = random(0, colors.size()-1);
        parse_connected_set(graph_data, set, color_id);
        ++iter;
    } build_html_graph(colors, graph_data);
}

/*
||=================================||
||       Cadenas de Valor       ||
||=================================||
*/
enum class Chain {
    MAX,
    MIN
};

pair<string, string>* parse_chain(Digraph<Registered>* pGraph) {
    pair<string, string>* graph_data = new pair<string,string>;
    for (int index_a = 0; index_a < pGraph->get_size(); ++index_a) {
        Vertex<Registered>* current = pGraph->get_vertex(index_a);
        int color_id = int(current->is_processed());
        graph_data->first.append(parse_user(current, color_id));
        for (int index_b = 0; index_b < current->link_quantity();) {
            NodeLink<Registered>* link = current->get_link(index_b);
            graph_data->second.append(parse_link(link));
            ++index_b;
        }
    } return graph_data;
}

void output_longest_chain(Digraph<Registered>* pGraph, Vertex<Registered>* pStart, Chain pSearch) {
    vector<string> colors = {"#8b7d92","#f75252"};
    Vertex<Registered>* last_node = nullptr;
    switch (pSearch) {
        case Chain::MAX:
            last_node = max_concurrency_chain(pGraph, pStart);
            break;
        case Chain::MIN:
            last_node = min_concurrency_chain(pGraph, pStart);
            break;
    } while (last_node != nullptr) {
        last_node->set_processed(true);
        last_node = last_node->get_previous();
    } build_html_graph(colors, parse_chain(pGraph));
}



void display_menu() {

}
