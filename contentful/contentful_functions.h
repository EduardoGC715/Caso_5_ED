#pragma once
#include <sstream>
#include "../ADT/Digraph.h"
#include "../ADT/BP_Tree.h"
#include "contentful.h"
#include <queue>

class contentful_functions {
private:
    vector<Registered*> all_regs;
    Contenful m_regs;
public:
    contentful_functions(){
        all_regs= m_regs.getRecords();
    }




    string get_nickname(){
        bool valid=false;
        char nick[33];
        string nickname;
        while(!valid){
            scanf("%32s", &nick );
            nickname=nick;
            if(find_nickname(nickname)==-1){
                if(nickname.length()>10){
                    valid=true;
                }
                //unvalid
            }
        }
        return nickname;
    }

    string get_password(){
        bool valid=false;
        char pass[21];
        char pass_con[21];
        string password;
        string password_con;

        while(!valid){
            scanf("%20s",&pass);
            password=pass;
            //confirmation
            scanf("%20s",&pass_con);
            password_con=pass_con;
            if(password==password_con){
                valid=true;
            }
            //unvalid
        }
        return password;
    }

    string get_description(){//in GUI add option to choose where to add; if offer or if demand
        char descri[251];
        string description;
        scanf("%250s",&descri);
        description=descri;
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