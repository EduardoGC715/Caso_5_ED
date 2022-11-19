#include <random>

#ifndef RANDOM
#define RANDOM
    static int random(int min, int max){
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distribution(min,max);// set range
        return distribution(gen); //generate random number
    }

#endif
