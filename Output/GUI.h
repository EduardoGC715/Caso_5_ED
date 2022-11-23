#pragma once
#include <iostream>
#include <fstream>
#include <windows.h>
#include "../contentful/Registered.h"

using std::pair;
using std::ofstream;
using std::ifstream;

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

pair<string, string>* parse_graph(Digraph<Registered>* pGraph) {
    pair<string, string>* graph_data = new pair<string,string>;
    for (int index_a = 0; index_a < pGraph->get_size(); ++index_a) {
        Vertex<Registered>* current = pGraph->get_vertex(index_a);
        graph_data->first.append(parse_user(current, 0));
        for (int index_b = 0; index_b < current->link_quantity();) {
            NodeLink<Registered>* link = current->get_link(index_b);
            graph_data->second.append(parse_link(link));
            ++index_b;
        }
    } return graph_data;
}

void fullgraph_html(Digraph<Registered>* pGraph) {
    pair<string, string>* graph_data = parse_graph(pGraph);
    string colors = "        \"#216be5\", \"#ff9440\"";
    ofstream file_output;
    ifstream file_template;
    string path = "Output\\index.html";
    file_output.open(path, ostream::out | ofstream::trunc);
    file_template.open("templates\\html_template.txt");

    string line;
    int line_num = 1;
    while (getline(file_template, line) && line_num != 13) {
        file_output << line << "\n";
        ++line_num;
    }
    file_output << graph_data->first; // Inserts node data
    while (getline(file_template, line) && line_num != 15) {
        file_output << line << "\n";
        ++line_num;
    }
    file_output << graph_data->second; // Inserts link data
    while (getline(file_template, line) && line_num != 60) {
        file_output << line << "\n";
        ++line_num;
    } file_output << colors << "\n";
    
    while (getline(file_template, line)) {
        file_output << line << "\n";
    } file_template.close();
    file_output.close();
    return;
}





string reg_to_string(vector<Registered*> regs){
    string html_nodes="\nnodes: [";
    string html_links="],\n"   "  links: [";
    for(auto reg:regs){
        html_nodes+="\n   { name: \""+reg->getNickname()+"\" ,offer:\""+reg->getOffer()+"\",demand:\""+reg->getOffer()+"\"},";
        //html_links+="\n   { source: \""+reg.getNickname()+"\", target: \""get.al que cumple"\" },"; debe ser un ciclo
    }
    //TODO temporary
    html_links+="\n { source: \"OriSolis25\", target: \"poly_bridgers\" },\n"
                "   { source: \"poly_bridgers\", target: \"Green_Lion\" },\n"
                "   { source: \"Green_Lion\", target: \"SuperSmashCoders122\" },\n"
                "   { source: \"SuperSmashCoders122\", target: \"PapaNoel2512\" },\n"
                "   { source: \"PapaNoel2512\", target: \"SantaClaus37\" },\n"
                "   { source: \"SantaClaus37\", target: \"the_agustd7\" }";

    html_nodes.pop_back();
    //html_links.pop_back()
    html_links+="      \n]\n"
                "     };\n";

    html_nodes+=html_links;
    return html_nodes;
}
