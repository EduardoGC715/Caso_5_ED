#include "ADT/BP_Tree.h"
#include "contentful/contentful_functions.h"
using namespace std;
int main(){
    auto contentful_f= new contentful_functions();
    contentful_f->print_all_regs();
    cout<<contentful_f->string_minimizer("metal_year_2000",2)<<endl;
    cout<<contentful_f->string_minimizer("rock_odin_gold",1)<<endl;
    /*
    auto tree= new BP_Tree<string>(5);
    tree->insert("a");
    tree->insert("b");
    tree->insert("c");
    tree->insert("d");
    tree->insert("e");
    tree->insert("f");
    tree->insert("a");

    if(tree->search("b")){
        cout<<"found\n";
    }
    tree->bpt_print();*/
    return 0;
}