#ifndef MOD_NUM_H
#define MOD_NUM_H

#include <iostream>
#include <vector>
#include "Whole_Num.h"

using std::vector;

class Mod_Num
{
    private:
        Whole_Num _number;
        Whole_Num _modulo;

    public:
        Mod_Num(); // Default Constructor
        ~Mod_Num(); // Destructor
        Mod_Num(Whole_Num number, Whole_Num modulo); // Num & Mod Constructor

        void setNum(Whole_Num n); // Sets _number
        void setMod(Whole_Num m); // Sets _modulo

        Whole_Num getNum() const; // Gets _number
        Whole_Num getMod() const; // Gets _modulo

        friend std::ostream& operator<<(std::ostream& os, const Mod_Num& num); // output
};






#endif