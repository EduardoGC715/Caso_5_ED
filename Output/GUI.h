#pragma once
#include <iostream>
#include <fstream>
#include <windows.h>
#include "../contentful/Registered.h"

void show_html(string& pPath){
    ShellExecute(nullptr, "open", pPath.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
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

void create_graph_UI(vector<Registered*> regs){
    const char *path="..\\Output\\test.html";
    std::ofstream graph_GUI(path);
    string html_file;

    html_file="<!DOCTYPE html>\n"
              "<meta charset=\"utf-8\" />\n"
              "<svg width=\"1920\" height=\"1080\"></svg>\n"
              "<script src=\"https://d3js.org/d3.v4.min.js\"></script>\n"
              "<script>\n"
              " //initilize svg or grab svg\n"
              " var svg = d3.select(\"svg\");\n"
              " var width = svg.attr(\"width\");\n"
              " var height = svg.attr(\"height\");\n"
              "\n"
              " var graphData = {\n";
    html_file+= reg_to_string(regs);
    html_file+="var simulation = d3\n"
               "         .forceSimulation(graphData.nodes)\n"
               "         .force(\"charge\", d3.forceManyBody().strength(-750))\n"
               "         .force(\"center\", d3.forceCenter(width / 2, height / 2))\n"
               "         .force(\"link\", d3.forceLink(graphData.links).id(d => d.name))\n"
               "         .on(\"tick\", ticked);\n"
               "\n"
               " var links = svg\n"
               "         .append(\"g\")\n"
               "         .selectAll(\"line\")\n"
               "         .data(graphData.links)\n"
               "         .enter()\n"
               "         .append(\"line\")\n"
               "         .attr(\"stroke-width\", 3)\n"
               "         .attr('marker-end', 'url(#mark-end-arrow)')\n"
               "         .style(\"stroke\", \"Black\");\n"
               "\n"
               " links.append(\"text\").text(d => d.name);\n"
               " var defs = svg.append('svg:defs');\n"
               " defs.append('svg:marker')\n"
               "         .attr('id', 'end-arrow')\n"
               "         .attr('viewBox', '0 -5 10 10')\n"
               "         .attr('refX', \"32\")\n"
               "         .attr('markerWidth', 2)\n"
               "         .attr('markerHeight', 2)\n"
               "         .attr('orient', 'auto')\n"
               "         .append('svg:path')\n"
               "         .attr('d', 'M0,-L10,0L0,5');\n"
               "\n"
               " // define arrow markers for leading arrow\n"
               " defs.append('svg:marker')\n"
               "         .attr('id', 'mark-end-arrow')\n"
               "         .attr('viewBox', '0 -5 10 10')\n"
               "         .attr('refX', 20)\n"
               "         .attr('markerWidth', 3.5)\n"
               "         .attr('markerHeight', 3.5)\n"
               "         .attr('orient', 'auto')\n"
               "         .append('svg:path')\n"
               "         .attr('d', 'M0,-5L10,0L0,5');\n"
               "\n"
               " var nodes = svg\n"
               "         .append(\"g\")\n"
               "         .selectAll(\"circle\")\n"
               "         .data(graphData.nodes)\n"
               "         .enter()\n"
               "         .append(\"circle\")\n"
               "         .attr(\"r\", 12)\n"
               "         .attr(\"fill\", \"orange\");\n"
               "\n"
               " var texts = svg\n"
               "         .append(\"g\")\n"
               "         .selectAll(\"text\")\n"
               "         .data(graphData.nodes)\n"
               "         .enter()\n"
               "         .append(\"text\")\n"
               "         .text(d => d.name);\n"
               "\n"
               " var drag = d3\n"
               "         .drag()\n"
               "         .on(\"start\", dragstarted)\n"
               "         .on(\"drag\", dragged)\n"
               "         .on(\"end\", dragended);\n"
               "\n"
               " nodes.call(drag);\n"
               "\n"
               " function ticked() {\n"
               "  texts.attr(\"x\",d => d.x);\n"
               "  texts.attr(\"y\",d => d.y);\n"
               "  //updating the position\n"
               "  nodes\n"
               "          .attr(\"cx\", function(d) {\n"
               "           return d.x;\n"
               "          })\n"
               "          .attr(\"cy\", function(d) {\n"
               "           return d.y;\n"
               "          });\n"
               "\n"
               "  links\n"
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
               "  console.log(simulation.alpha());\n"
               " }\n"
               "\n"
               " function dragstarted(d) {\n"
               "  //your alpha hit 0 it stops! make it run again\n"
               "  simulation.alphaTarget(0.3).restart();\n"
               "  d.fx = d3.event.x;\n"
               "  d.fy = d3.event.y;\n"
               " }\n"
               " function dragged(d) {\n"
               "  d.fx = d3.event.x;\n"
               "  d.fy = d3.event.y;\n"
               " }\n"
               "\n"
               " function dragended(d) {\n"
               "  // alpha min is 0, head there\n"
               "  simulation.alphaTarget(0);\n"
               "  d.fx = null;\n"
               "  d.fy = null;\n"
               " }\n"
               "</script>";
    graph_GUI << html_file;
}
