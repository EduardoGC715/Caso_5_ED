#pragma once
#include <sstream>
#include "../ADT/BP_Tree.h"
#include "contentful.h"

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
        return minimized;
    }

    void bp_insert(vector<string> &to_add,BP_Tree<string> &t_tree){
        for(auto & word : to_add){
            t_tree.insert(word);
        }
    }

    int get_match_value(std::vector<string> leaves){
        std::string current;
        int value=0;
        for(int i=0;i<leaves.size();i++){
            current=leaves[i];
            for(int j=i+1;j<leaves.size();j++){
                if(current==leaves[j]){
                    value++;
                }
            }
        }
        return value;
    }

    void match_maker(vector<string> &users){//TODO: vector de struct User
            for(int pos=0;pos<users.size();pos++){
                if(users[pos+1].type=="offerer" || user[pos+1=="both"]){
                    BP_Tree<string> match_tree (5);

                    bp_insert(string_minimizer(),nick_tree);
                }
                demand = string_minimizer(pos,2);
                bp_insert(demand,nick_tree);
                match_values.push_back(get_match_value(nick_tree.get_leaves()));
            }
    }
};