#pragma once
#include <sstream>
#include "../ADT/Digraph.h"
#include "../ADT/BP_Tree.h"
#include "contentful.h"
#include <queue>
#include "../utils/Date.h"

class contentful_functions {
private:
    vector<Registered*> all_regs;
    Contenful m_regs;
public:
    contentful_functions(){
        all_regs= m_regs.getRecords();
    }

    void display_menu(){
        int option_m=0;
        int option_d=0;
        string nickname;
        string password;
        string offer;
        string demand;
        Date current(false);
        bool done=false;
        bool finished=false;
        while(!done) {
            printf("Bienvenido a Gobiz!\n"
                   "Digite el numero para seleccionar la opcion que desea.\n"
                   "1. Para crear un nuevo usuario.\n"
                   "2. Para consultar matches de oferta de un nickname.\n"
                   "3. Para consultar matches de demanda de un nickname.\n"
                   "4. Para visualizar los comercios circulares.\n"
                   "5. Para visualizar la cadena de valor mas larga con mayor concurrencia.\n"
                   "6. Para visualizar la cadena de valoe mas larga con menor concurrencia.\n"
                   "7. Para visualizar el Top 10 de servicios o productos mas codiciados.\n"
                   "8. Para visualizar la areas de mercado conexas.\n"
                   "9. Para salir.\n");
            cin>>option_m;
            if (option_m == 1) {
                nickname = get_nickname();
                password = get_password();
                printf("Seleccione si desea:\n"
                       "1. Ofertar.\n"
                       "2. Demandar.\n"
                       "3. Ambas.\n");
                while(!finished){
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cin>>option_d;
                    if(option_d==1){
                        printf("Digite la oferta: ");
                        offer = get_description();
                        finished=true;
                        option_d=0;
                    }
                    else if(option_d==2){
                        printf("Digite la demanda: ");
                        demand = get_description();
                        finished=true;
                        option_d=0;
                    }
                    else if(option_d==3){
                        printf("Digite la oferta: ");
                        offer = get_description();
                        printf("Digite la demanda: ");
                        demand = get_description();
                        finished=true;
                        option_d=0;
                    }
                    else{
                        printf("Opcion incorrecta, intenta de nuevo.");
                    }
                }
                reg_user(nickname, offer,demand, password,current.get_day(),current.get_month(),current.get_year());
            }
            else if (option_m == 2) {
                printf("option 2");
            }
            else if (option_m == 3) {
                printf("option 3");
            }
            else if (option_m == 4) {
                printf("option 4");
            }
            else if (option_m == 5) {
                printf("option 5");
            }
            else if (option_m == 6) {
                printf("option 6");
            }
            else if (option_m == 7) {
                printf("option 7");
            }
            else if (option_m == 8) {
                printf("option 8");
            }
            else if (option_m == 9) {
                done=true;
            }
            else{
                printf("Opcion invalida, intenta de nuevo.");
            }
        }
    }

    string get_nickname(){
        string nickname;
        while(true){
            printf("Digite el usuario: ");
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin>>nickname;
            if(find_nickname(nickname)==-1){
                if(nickname.length()>10){
                    break;
                }
            }
            printf("El usuario ingresado es invalido.\n");
        }
        return nickname;
    }

    string get_password(){
        bool valid=false;
        string password;
        string password_con;

        while(true){
            printf("Digite una contraseña: ");
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin>>password;
            printf("Digite la contraseña de nuevo: ");
            cin>>password_con;
            if(password==password_con){
                break;
            }
            printf("La contraseña no coincide.");
        }
        return password;
    }

    string get_description(){//in GUI add option to choose where to add; if offer or if demand
        string description;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin >> std::ws, description);
        return description;
    }
    void reg_user(string t_nick, string t_offer, string t_demand, string t_password, int t_day, int t_month, int t_year){
        m_regs.registerUser(t_nick,t_offer,t_demand,t_password,t_day,t_month,t_year);
    }
    void print_all_regs(){
        int index=0;
        for(auto & reg : all_regs){
            cout<<"\nRegister #"<<index++<<endl;
            cout<<"Nickname: "<<reg->getNickname()<<endl;
            cout<<"Date: "<<reg->getPostdate()<<endl;
            cout<<"Offer: "<<reg->getOffer()<<endl;
            cout<<"Demand: "<<reg->getDemand()<<endl;
        }
    }
    int find_nickname(string t_nick){
        auto found = find_if(all_regs.begin(), all_regs.end(), [&t_nick](Registered *obj) {return obj->getNickname() == t_nick;});
        if (found != all_regs.end()){
            auto index = std::distance(all_regs.begin(), found);
            return index;
        }
        return -1;
    }
    vector<string> string_minimizer(string to_min){
        vector<string> minimized;
        istringstream iss(to_min);
        int wrd_size;
        string word;
        while (iss>>word){
            wrd_size=int(word.length());
            if(wrd_size==4){
                minimized.insert(minimized.end(),word + " ");
            }
            else if(wrd_size>4){
                for(int j=0; j<wrd_size*0.4;j++){
                    word.pop_back();
                }
                minimized.insert(minimized.end(),word + " ");
            }
        }
        minimized.erase( std::unique(minimized.begin(), minimized.end()), minimized.end());
        return minimized;
    }

    void bp_insert(vector<string> to_add,BP_Tree<string> &t_tree){
        for(auto & word : to_add){
            t_tree.insert(word);
        }
    }

    int get_match_value(std::vector<string> leaves){
        std::string current_i;
        string current_j;
        int total=0;
        for(int i=0;i<leaves.size();i++){
            int value = 0;
            current_i=leaves[i];
            for(int j=i+1;j<leaves.size();j++){
                current_j=leaves[j];
                if(current_i==current_j){
                    value+=value+1;
                }
            }
            total+=value;
        } return total;
    }

    void match_maker(vector<Registered*> &users, Digraph<Registered>* pGraph){
        int match_value=0;
        for(int pos_i=0;pos_i<users.size();pos_i++){
            Registered* user_i = users.at(pos_i);
            if (user_i->getType() != "demander"){
                for(int pos_j=0; pos_j<users.size(); pos_j++){
                    Registered* user_j = users.at(pos_j);
                    if(user_j->getType() != "offerer" && pos_i != pos_j){
                        BP_Tree<string> match_tree (5);
                        bp_insert(string_minimizer(user_i->getOffer()), match_tree);
                        bp_insert(string_minimizer(user_j->getDemand()),match_tree);
                        match_value = get_match_value(match_tree.get_leaves());
                        if(match_value>5){

                            //TODO fecha
                            pGraph->join(pos_i, pos_j, match_value);
                        }
                    }
                }
            }
        }
    }

    vector<string> remove_repeated(string repeated,vector<string> descrptn){//removes ALL repeated words in a vector given the word to remove
        std::vector<string>::iterator itr;
        while(true){
            itr = find(descrptn.begin(), descrptn.end(), repeated);
            if(itr!=descrptn.end()){
                descrptn.erase(itr);
            }
            else{
                break;
            }
        }
        return descrptn;
    }

    //TODO funcion que de todos los nodos del grafo me de un vector de string que contenga tanto las ofertas como las demandas de todos.

    priority_queue<tuple<int, string>> most_repeated(vector<string> to_analize){
        vector<string> simp_descrptns;
        string all_descrptns;
        vector<string> ocurrences;
        string word;
        BP_Tree<string> ocurrences_tree(5);
        priority_queue<tuple<int, string>> rankings;
        string simplified;

        for(auto descrptn:to_analize){
            vector<string> analized =  string_minimizer(descrptn);
            for(auto word_s:analized){
                simplified+=" "+word_s;
            }
        }
        istringstream iss(simplified);
        while (iss>>word) {
            ocurrences_tree.insert(word);
        }
        ocurrences = ocurrences_tree.get_leaves();

        int aux_value;
        string current;
        while(!ocurrences.empty()){
            current=ocurrences[0];
            aux_value=1;
            for(int pos_j=1;pos_j<ocurrences.size();pos_j++){
                if(current==ocurrences[pos_j]){
                    aux_value++;
                }
            }
            tuple<int, string> rank = make_tuple(aux_value,current);
            rankings.push(rank);
            ocurrences = remove_repeated(current,ocurrences);
        }
        return rankings;
    }
    vector<Registered*> get_all_regs(){
        return all_regs;
    }
};