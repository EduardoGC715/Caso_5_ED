#include "contentful/contentful_functions.h"
#include "Output/GUI.h"
using namespace std;
int main(){
    create_html();
    LPCTSTR test = "..\\Output\\test.html";
    show_html(test);
}