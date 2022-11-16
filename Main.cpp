#include "ADT/BP_Tree.h"

using namespace std;
int main(){
    auto tree= new BP_Tree<string>(5);
    tree->insert(string ("a"));
    tree->insert(new string("b"));
    tree->insert(new string("c"));
    tree->insert(new string("d"));
    tree->insert(new string("e"));
    tree->insert(new string("f"));
    tree->insert(new string("f"));
    tree->insert(new string("f"));
    tree->insert(new string("f"));
    tree->insert(new string("f"));
    tree->insert(new string("f"));
    tree->insert(new string("f"));




    tree->bpt_print();
    return 0;
}