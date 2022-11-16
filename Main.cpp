#include "ADT/BP_Tree.h"

using namespace std;
int main(){
    auto arbol= new BP_Tree<string>(5);
    arbol->insert(string ("a"));
    arbol->insert(new string("b"));
    arbol->insert(new string("c"));
    arbol->insert(new string("d"));
    arbol->insert(new string("e"));
    arbol->insert(new string("f"));
    arbol->insert(new string("f"));
    arbol->insert(new string("f"));
    arbol->insert(new string("f"));
    arbol->insert(new string("f"));
    arbol->insert(new string("f"));
    arbol->insert(new string("f"));




    arbol->print_tree(arbol->get_root(),1);
    return 0;
}