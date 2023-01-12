#include <iostream>
#include <vector>
#include "Whole_Num.h"
#include "Mod_Num.h"

using std::vector;
using std::cout;
using std::endl;
using std::cin;

int main()
{
    Mod_Num x = Mod_Num("54", "29");
    cout << x << endl;

    return 0;
}