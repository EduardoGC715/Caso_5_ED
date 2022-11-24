# include "contentful/contentful_functions.h"
# include "ADT/Digraph.h"
# include "Output/GUI.h"
using namespace std;
int main(){
    vector<string> options;





    contentful_functions regs;
    vector<Registered*> all_users = regs.get_all_regs();
    Digraph<Registered>* graph = new Digraph<Registered>;
    for (int index = 0; index < all_users.size(); ++index) {
        Registered* user = all_users.at(index);
        graph->insert_vertex(user);
    }

    regs.match_maker(all_users, graph);
<<<<<<< HEAD
    output_graph(graph);
    // output_connected_sets(graph);
    /* create_graph_UI(regs.get_all_regs());
    string path = "Output\\test_2.html";
    show_html(path); */
=======
    fullgraph_html(graph);
    // create_graph_UI(regs.get_all_regs());
    string path = "..\\Output\\index.html";
    show_html(path);
>>>>>>> bdacd7c7e9b60af322612fb059902bc5a2623fc4
}