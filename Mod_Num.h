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




};






#endif