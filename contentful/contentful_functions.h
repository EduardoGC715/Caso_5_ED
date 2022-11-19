#pragma once
#include <sstream>
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
        std::string current;
        int value;
        for(int i=0;i<leaves.size();i++){
            current=leaves[i];
            for(int j=i+1;j<leaves.size();j++){
                if(current==leaves[j]){
                    value+=value+1;
                }
            }
        }
        return value;
    }


    void match_maker(vector<Registered> &users){
        int mtch_value;
        for(int pos_i=0;pos_i<users.size();pos_i++){
            if(users[pos_i].getType()!="demander"){
                for(int pos_j=pos_i+1;pos_j<users.size();pos_j++){
                    if(users[pos_j].getType()!="offerer"){
                        BP_Tree<string> match_tree (5);
                        bp_insert(string_minimizer(users[pos_i].getOffer()),match_tree);
                        bp_insert(string_minimizer(users[pos_j].getDemand()),match_tree);
                        mtch_value = get_match_value(match_tree.get_leaves());
                        if(mtch_value>4){
                            //TODO: add link
                        }
                    }
                }
            }
        }
    }

    vector<string> remove_repeated(string repeated,vector<string> descrptn){//removes ALL reeated words in a vector given the word to remove
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
    }

    priority_queue<tuple<int, string>> most_repeated(vector<string> to_analize){
        vector<string> simp_descrptns;
        string all_descrptns;
        vector<string> ocurrences;
        string word;
        BP_Tree<string> ocurrences_tree(5);
        priority_queue<tuple<int, string>> rankings;

        for(auto descrptn:to_analize){
            simp_descrptns = string_minimizer(descrptn);
        }
        for(auto simp_descr:simp_descrptns){
            all_descrptns+=" "+simp_descr;
        }
        istringstream iss(all_descrptns);
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
};