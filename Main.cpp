#include "ADT/BP_Tree.h"
#include "contentful/contentful.h"
using namespace std;
int main(){

    Contenful regs;

    //regs.registerUser("badbunny_in_concert", "conciertos a estadio lleno de gente escuchando pum pum con el mismo acorde por 2 horas", "transporte y seguridad en todos los paises que visita y mucha fiesta tambien", "conejo123", 02, 11, 2022);
    vector<Registered*> allrecords = regs.getRecords();
    cout << allrecords.at(0)->getNickname() << endl;
    
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
    tree->bpt_print();
    return 0;
}