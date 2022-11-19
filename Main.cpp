#include "contentful/contentful_functions.h"
using namespace std;
int main(){
    contentful_functions trials;
    auto minimized = trials.string_minimizer("hola mi nombre es eduardo eduardo");
    for(auto word:minimized){
        cout<<word<<endl;
    }
    return 0;
}