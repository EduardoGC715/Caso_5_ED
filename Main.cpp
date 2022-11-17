#include "contentful/contentful_functions.h"
using namespace std;
int main(){
    auto contentful_f= new contentful_functions();
    contentful_f->print_all_regs();
    vector<int> matches =contentful_f->match_maker("metal_year_2000",2);
    for(int i=0;i<matches.size();i++){
        cout<<"\nmatch "<<i<<" :"<< matches[i];
    }

    /*auto tree= new BP_Tree<string>(5);
    tree->insert("a");
    tree->insert("b");
    tree->insert("c");
    tree->insert("d");
    tree->insert("e");
    tree->insert("f");
    tree->insert("a");
    for(int i=0;i<tree->get_leaves_s().size();i++){
        cout<<tree->get_leaves_s()[i];
    }
    tree->bpt_print();*/
    return 0;
}