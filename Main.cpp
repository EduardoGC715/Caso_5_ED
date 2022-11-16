#include "ADT/BP_Tree.h"

using namespace std;
int main(){
    auto tree= new BP_Tree<string>(5);
    tree->insert("a");
    tree->insert("b");
    tree->insert("c");
    tree->insert("d");
    tree->insert("e");
    tree->insert("f");
    tree->insert("a");

    tree->bpt_print();
    return 0;
}