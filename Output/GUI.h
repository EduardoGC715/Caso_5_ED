#pragma once
#include <iostream>
#include <fstream>
#include <windows.h>
#include "../contentful/Registered.h"

void show_html(LPCTSTR path){
    ShellExecute(nullptr, "open", path, nullptr, nullptr, SW_SHOWNORMAL);
}

string reg_to_string(vector<Registered*> regs){
    string html_nodes;
    string html_links="\n  ],\n"   "  links: [";
    for(auto reg:regs){
        html_nodes+="\n   { name: \""+reg->getNickname()+"\" ,offer:\""+reg->getOffer()+"\",demand:\""+reg->getOffer()+"\"},";
        //html_links+="\n   { source: \""+reg.getNickname()+"\", target: \""get.al que cumple"\" },"; debe ser un ciclo
    }
    html_nodes.pop_back();
    //html_links.pop_back()
    //TODO temporary
    html_links+="\n   { source: \"OriSolis25\", target: \"poly_bridgers\" },\n"
                "   { source: \"poly_bridgers\", target: \"Green_Lion\" },\n"
                "   { source: \"Green_Lion\", target: \"SuperSmashCoders122\" },\n"
                "   { source: \"SuperSmashCoders122\", target: \"PapaNoel2512\" },\n"
                "   { source: \"PapaNoel2512\", target: \"SantaClaus37\" },\n"
                "   { source: \"SantaClaus37\", target: \"the_agustd7\" }";

    html_links+="      \n]\n"
                "     };\n";

    html_nodes+=html_links;
    return html_nodes;
}

void create_graph_UI(vector<Registered*> regs){
    const char *path="..\\Output\\test.html";
    std::ofstream graph_GUI(path);
    string html_file;

    html_file="<!DOCTYPE html>\n"
                        "<meta charset=\"utf-8\" />\n"
                        "<style>\n"
                        " .links line {\n"
                        "  stroke: #999;\n"
                        "  stroke-opacity: 0.6;\n"
                        " }\n"
                        "\n"
                        " .nodes circle {\n"
                        "  stroke: #fff;\n"
                        "  stroke-width: 1.5px;\n"
                        " }\n"
                        "</style>\n"
                        "<svg width=\"960\" height=\"600\"></svg>\n"
                        "<script src=\"https://d3js.org/d3.v4.min.js\"></script>\n"
                        "<script>\n"
                        " //initilize svg or grab svg\n"
                        " var svg = d3.select(\"svg\");\n"
                        " var width = svg.attr(\"width\");\n"
                        " var height = svg.attr(\"height\");\n"
                        "\n"
                        " //intialize data\n"
                        " var graph = {\n"
                        "  nodes: [";
    html_file+= reg_to_string(regs);
    html_file+="var simulation = d3\n"
               "         .forceSimulation(graph.nodes)\n"
               "         .force(\n"
               "                 \"link\",\n"
               "                 d3\n"
               "                         .forceLink()\n"
               "                         .id(function(d) {\n"
               "                          return d.name;\n"
               "                         })\n"
               "                         .links(graph.links)\n"
               "         )\n"
               "\n"
               "         .force(\"charge\", d3.forceManyBody().strength(-30))\n"
               "         .force(\"center\", d3.forceCenter(width / 2, height / 2))\n"
               "         .on(\"tick\", ticked);\n"
               "\n"
               " var link = svg\n"
               "         .append(\"g\")\n"
               "         .attr(\"class\", \"links\")\n"
               "         .selectAll(\"line\")\n"
               "         .data(graph.links)\n"
               "         .enter()\n"
               "         .append(\"line\")\n"
               "         .attr(\"stroke-width\", function(d) {\n"
               "          return 3;\n"
               "         });\n"
               "\n"
               " var node = svg\n"
               "         .append(\"g\")\n"
               "         .attr(\"class\", \"nodes\")\n"
               "         .selectAll(\"circle\")\n"
               "         .data(graph.nodes)\n"
               "         .enter()\n"
               "         .append(\"circle\")\n"
               "         .attr(\"r\", 5)\n"
               "         .attr(\"fill\", function(d) {\n"
               "          return \"red\";\n"
               "         })\n"
               "         .call(\n"
               "                 d3\n"
               "                         .drag()\n"
               "                         .on(\"start\", dragstarted)\n"
               "                         .on(\"drag\", dragged)\n"
               "                         .on(\"end\", dragended)\n"
               "         );\n"
               "\n"
               " function ticked() {\n"
               "  link\n"
               "          .attr(\"x1\", function(d) {\n"
               "           return d.source.x;\n"
               "          })\n"
               "          .attr(\"y1\", function(d) {\n"
               "           return d.source.y;\n"
               "          })\n"
               "          .attr(\"x2\", function(d) {\n"
               "           return d.target.x;\n"
               "          })\n"
               "          .attr(\"y2\", function(d) {\n"
               "           return d.target.y;\n"
               "          });\n"
               "\n"
               "  node\n"
               "          .attr(\"cx\", function(d) {\n"
               "           return d.x;\n"
               "          })\n"
               "          .attr(\"cy\", function(d) {\n"
               "           return d.y;\n"
               "          });\n"
               " }\n"
               "\n"
               " function dragstarted(d) {\n"
               "  if (!d3.event.active) simulation.alphaTarget(0.3).restart();\n"
               "  d.fx = d.x;\n"
               "  d.fy = d.y;\n"
               "  console.log(d3.event.subject);\n"
               " }\n"
               "\n"
               " function dragged(d) {\n"
               "  d.fx = d3.event.x;\n"
               "  d.fy = d3.event.y;\n"
               " }\n"
               "\n"
               " function dragended(d) {\n"
               "  if (!d3.event.active) simulation.alphaTarget(0);\n"
               "  d.fx = null;\n"
               "  d.fy = null;\n"
               " }\n"
               "</script>";
    graph_GUI << html_file;
}
