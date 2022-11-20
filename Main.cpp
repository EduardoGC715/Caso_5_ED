#include "contentful/contentful_functions.h"
using namespace std;
int main(){

    contentful_functions regs;

    vector<string> trial={"hola soy programador en python","me gustaria un programador en python",
    "Busco programador en python "," soy bueno en python","se el leguaje de python "," ocupo un programador en c"
    ,"Busco programador en c","busco programador bueno"};

    auto rankings = regs.most_repeated(trial);
    while(!rankings.empty()){
        auto rank = rankings.top();
        cout<<"Value "<<get<0>(rank)<<": "<<get<1>(rank)<<endl;
        rankings.pop();
    }
    return 0;
}