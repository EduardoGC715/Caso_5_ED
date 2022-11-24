# pragma once
# include <string>
#include "../utils/Date.h"

using std::string;

class Registered {
private:
    string nickname;
    string offer;
    string demand;
    Date* postdate;
    //TODO map de fechas.
    Date* matchdate;
    string type;

public:
    Registered(string pNickname, string pOffer, string pDemand, string pPostdate) {
        this->nickname = pNickname;
        this->offer = pOffer;
        this->demand = pDemand;
        this->postdate = new Date(pPostdate);
        this->matchdate= new Date(false);
        if(!offer.empty() && !demand.empty()){
            type="both";
        }
        else if(!offer.empty()){
            type="offerer";
        }
        else{
            type="demander";
        }
    }

    string getNickname() {
        return this->nickname;
    }

    string getOffer() {
        return this->offer;
    }

    string getDemand() {
        return this->demand;
    }

    Date* getPostdate() {
        return this->postdate;
    }
    Date* getMatchdate() {
        return this->matchdate;
    }

    string getType(){
        return this->type;
    }
};