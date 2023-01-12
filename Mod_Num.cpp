#include "Mod_Num.h"
#include "Whole_Num.h"
#include <iostream>
#include <vector>

// Default Constructor
Mod_Num::Mod_Num(): _number("0"), _modulo("1")
{}

// Destructor
Mod_Num::~Mod_Num()
{}

// Num & Mod Constructor
Mod_Num::Mod_Num(Whole_Num number, Whole_Num modulo)
{
    if (modulo <= "0")
    {throw std::invalid_argument("Mod value cannot be less than or equal to zero");}

    else
    {
        _number = number % modulo;
        _modulo = modulo;
    }
}


// Sets _number
void Mod_Num::setNum(Whole_Num)
{}

// Sets _modulo
void Mod_Num::setMod(Whole_Num)
{}



// output
std::ostream& operator<<(std::ostream& os, const Mod_Num& num)
{
    if (num._number.sign() == '-')
    {os << num._number.sign();}

    for (size_t i = 0; i < num._number.size(); i++)
    {os << num._number.at(i);}

    return os;
}