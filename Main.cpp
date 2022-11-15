#include "ADT/BP_Tree.h"

int main(){
    auto arbol= new BP_Tree<int>(3);
    arbol->insert(1);
    arbol->insert(2);
    arbol->insert(3);
    arbol->insert(4);
    arbol->insert(5);

    arbol->print_tree(arbol->get_root());
    return 0;
}