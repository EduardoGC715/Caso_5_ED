#pragma once

#include <sstream>
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
        for(auto & reg : all_regs){
            cout<<"\nNickname: "<<reg->getNickname()<<endl;
            cout<<"Date: "<<reg->getPostdate()<<endl;
            cout<<"Offer: "<<reg->getOffer()<<endl;
            cout<<"Demand: "<<reg->getDemand()<<endl;
        }
    }
    string string_minimizer(string t_nick,int t_opt){
        auto found = find_if(all_regs.begin(), all_regs.end(), [&t_nick](Registered *obj) {return obj->getNickname() == t_nick;});
        if (found != all_regs.end()){
            auto index = std::distance(all_regs.begin(), found);
            string to_min;
            string minimized;
            if(t_opt==1){//minimize offer
                 to_min = all_regs.at(index)->getOffer();
            }
            else{//minimize demand
                to_min = all_regs.at(index)->getDemand();
            }
            istringstream iss(to_min);
            int wrd_size;
            string word;
            while (iss>>word){
                wrd_size=int(word.length());
                if(wrd_size==3){
                    minimized.append(word + " ");
                }
                else if(wrd_size>3){
                    for(int j=0; j<wrd_size-wrd_size*0.6;j++){
                        word.pop_back();
                    }
                    minimized.append(word + " ");
                }
            }
            return minimized;
        }
        else{
            //nick not found
        }
    }
};