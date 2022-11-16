#include "ADT/BP_Tree.h"

using namespace std;
int main(){
    auto arbol= new BP_Tree<int>(3);
    arbol->insert(new int(1));
    arbol->insert(new int(2));
    arbol->insert(new int(3));
    arbol->insert(new int(4));
    arbol->insert(new int(5));
    arbol->insert(new int(6));
    arbol->insert(new int(7));
    arbol->insert(new int(8));
    arbol->insert(new int(9));

    arbol->print_tree(arbol->get_root(),1);
    return 0;
}