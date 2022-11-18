# pragma once
# include <string>

using std::string;

class Registered {
private:
    string nickname;
    string offer;
    string demand;
    string postdate;

public:
    Registered(string pNickname, string pOffer, string pDemand, string pPostdate) {
        this->nickname = pNickname;
        this->offer = pOffer;
        this->demand = pDemand;
        this->postdate = pPostdate;
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

    string getPostdate() {
        return this->postdate;
    }
};