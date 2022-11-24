# include "contentful/contentful_functions.h"
# include "ADT/Digraph.h"
# include "Output/GUI.h"
using namespace std;
int main(){
    contentful_functions regs;
    vector<Registered*> all_users = regs.get_all_regs();
    Digraph<Registered>* graph = new Digraph<Registered>;
    for (int index = 0; index < all_users.size(); ++index) {
        Registered* user = all_users.at(index);
        graph->insert_vertex(user);
    }

    regs.match_maker(all_users, graph);
    fullgraph_html(graph);
    // create_graph_UI(regs.get_all_regs());
    string path = "..\\Output\\index.html";
    show_html(path);
}