#include "contentful/contentful_functions.h"
#include "Output/GUI.h"
using namespace std;
int main(){
    contentful_functions regs;
    create_graph_UI(regs.get_all_regs());
    LPCTSTR test = "..\\Output\\test.html";
    show_html(test);
}