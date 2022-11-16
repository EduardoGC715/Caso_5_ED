#include "contentful/contentful_functions.h"
using namespace std;
int main(){
    auto contentful_f= new contentful_functions();
    contentful_f->print_all_regs();
    vector<int> matches =contentful_f->match_maker("rock_odin_gold",1);
    for(int i=0;i<matches.size();i++){
        cout<<"match "<<i<<" :"<< matches[i]<<endl;
    }


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