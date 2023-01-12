#include "Whole_Num.h"
#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

void Whole_Num::_incNum()
{
    size_t i = size() - 1;
    _num[i] = _num[i] + 1;

    while ((i > 0) && (_num[i] == ':'))
    {
        _num[i] = '0';
        i--;
        _num[i] = _num[i] + 1;
    }

    if (_num[0] == ':')
    {
        _num.insert(_num.begin(), '1');
        _num[1] = '0';
    }
}

void Whole_Num::_decNum()
{
    size_t i = size() - 1;
    _num[i] = _num[i] - 1;

    while ((i > 0) && (_num[i] == '/'))
    {
        _num[i] = '9';
        i--;
        _num[i] = _num[i] - 1;
    }

    if (_num[0] == '0')
    {
        _num.erase(_num.begin());
    }

}

Whole_Num Whole_Num::_add(Whole_Num lhs, Whole_Num rhs)
{
    // Checks if the signs are equal (Both '+', '-', or '?')
    if (lhs.sign() == rhs.sign())
    {
        // Checks if they are both zero
        if (lhs.sign() == '?')
        {return lhs;}

        // Checks if they are both positive or negative
        else
        {
            vector<char> lNum = lhs._num;
            vector<char> rNum = rhs._num;
            
            // Checks the lengths of each number and matches their lengths
            if (lNum.size() != rNum.size())
            {
                while (lNum.size() < rNum.size())
                {lNum.insert(lNum.begin(), '0');}

                while (lNum.size() > rNum.size())
                {rNum.insert(rNum.begin(), '0');}
            }

            vector<char> sum = {};
            int carry = 0;

            // Adds the numbers by column
            for (int i = lNum.size() - 1; i >= 0; i--)
            {
                // Takes current number column digits
                char lDigit = lNum[i];
                char rDigit = rNum[i];

                // Adds the column numbers
                int colAdd = (lDigit - '0') + (rDigit - '0') + carry;

                if (colAdd > 9)
                {carry = 1;}

                else
                {carry = 0;}

                char digit = (colAdd % 10) + '0';
                sum.insert(sum.begin(), digit);
            }

            // checks if their is a remaining carry over
            if (carry == 1)
            {sum.insert(sum.begin(), carry + '0');}

            Whole_Num temp = "0";
            temp._sign = lhs.sign();
            temp._num = sum;
            return temp;
        }
    }

    // Checks if either of the signs are zero 
    else if (lhs.sign() == '?' || rhs.sign() == '?')
    {
        // Checks if lhs is zero and rhs is not
        if (lhs.sign() == '?')
        {return rhs;}

        // Checks if rhs is zero and lhs is not
        else
        {return lhs;}
    }

    else
    {throw std::invalid_argument("Different signs");}
}

Whole_Num Whole_Num::_sub(Whole_Num lhs, Whole_Num rhs)
{
    // Checks if either of the signs are zero 
    if (lhs.sign() == '?' || rhs.sign() == '?')
    {
        // Checks if lhs is zero and rhs is not
        if (lhs.sign() == '?')
        {return rhs;}

        // Checks if rhs is zero and lhs is not
        else
        {return lhs;}
    }

    // Checks if signs are different
    else if (lhs.sign() != rhs.sign())
    {
        Whole_Num temp = "0";
        bool rBigger = false;

        // Sets to lhs sign 
        if (lhs.abs() > rhs.abs())
        {temp._sign = lhs.sign();}

        // Sets to rhs sign
        else if (lhs.abs() < rhs.abs())
        {
            temp._sign = rhs.sign();
            rBigger = true;
        }

        // Sets to zero as they are the same absolute value
        else
        {return "0";}

        // Sets lhs and rhs values
        if (rBigger)
        {std::swap(lhs, rhs);}

        vector<char> lNum = lhs._num;
        vector<char> rNum = rhs._num;

        // Checks the lengths of each number and matches their lengths
        if (lNum.size() != rNum.size())
        {
            while (lNum.size() < rNum.size())
            {lNum.insert(lNum.begin(), '0');}

            while (lNum.size() > rNum.size())
            {rNum.insert(rNum.begin(), '0');}
        }

        vector<char> diff = {};

        // Adds the numbers by column
        for (int i = lNum.size() - 1; i >= 0; i--)
        {
            // Takes current number column digits
            char lDigit = lNum[i];
            char rDigit = rNum[i];

            // If top number is bigger/same as bottom number
            if (lDigit >= rDigit)
            {
                char digit = (lDigit - rDigit) + '0';
                diff.insert(diff.begin(), digit);
            }

            // If a number needs to be carried
            else
            {
                // Reaches number to carry from
                int j = i - 1;
                while (lNum[j] == '0')
                {j--;}

                lNum[j] = lNum[j] - 1;
                j++;

                // Returns to number 
                while (lNum[j] == '0' && j != i)
                {
                    lNum[j] = '9';
                    j++;
                }

                
                char digit = (((lNum[i] - '0') + 10) - (rNum[i] - '0')) + '0';
                diff.insert(diff.begin(), digit);
            }
        }

        while (diff[0] == '0')
        {diff.erase(diff.begin());}
        temp._num = diff;
        return temp;
    }

    // Checks if signs are the same
    else
    {throw std::invalid_argument("Same signs");}

}

Whole_Num Whole_Num::_mult(Whole_Num lhs, Whole_Num rhs)
{
    // Checks if either lhs or rhs are zeroes
    if (lhs == "0" || rhs == "0")
    {return "0";}

    // Checks if either lhs or rhs are 1
    else if (lhs == "1" || rhs == "1")
    {
        // Checks if lhs is 1 
        if (lhs == "1")
        {return rhs;}

        // Checks if rhs is 1
        else
        {return lhs;}
    }

    // Checks if either lhs or rhs are -1
    else if (lhs == "-1" || rhs == "-1")
    {
        // Checks if both are -1
        if (lhs == "-1" && rhs == "-1")
        {return "1";}

        // Checks if lhs is -1
        else if (lhs == "-1")
        {
            Whole_Num temp = "0";
            temp._num = rhs._num;

            // Checks if rhs is +
            if (rhs.sign() == '+')
            {temp._sign = '-';}

            // Checks if rhs is -
            else
            {temp._sign = '+';}

            return temp;
        }

        // Checks if rhs is -1
        else
        {
            Whole_Num temp = "0";
            temp._num = lhs._num;

            // Checks if lhs is +
            if (lhs.sign() == '+')
            {temp._sign = '-';}

            // Checks if lhs is -
            else
            {temp._sign = '+';}

            return temp;
        }
    }

    // Regular multiplication
    else
    {
        Whole_Num temp = "1";
        // Checks if either sign is a negative
        if (lhs.sign() == '-' || rhs.sign() == '-')
        {
            // If both are negative
            if (lhs.sign() == '-' && rhs.sign() == '-')
            {temp._sign = '+';}

            // If only one is negative
            else
            {temp._sign = '-';}
        }

        // Vectors to multiply
        vector<char> lNum = lhs._num;
        vector<char> rNum = rhs._num;

        // Swaps vectors if lNum is bigger
        if (lNum.size() < rNum.size())
        {std::swap(lNum, rNum);}

        Whole_Num product = "0";
        int loopCnt = 0;
        // iterates the lower number rNum
        for (int i = rNum.size() - 1; i >= 0; i--)
        {
            int bNum = rNum[i] - '0';
            int carry = 0;

            Whole_Num currLine = "0";
            currLine._num.clear();
            currLine._sign = '+';

            for (int j = 0; j < loopCnt; j++)
            {currLine._num.insert(currLine._num.begin(),'0');}


            for (int j = lNum.size() - 1; j >= 0; j--)
            {
                int tNum = lNum[j] - '0';
                int prod = (tNum * bNum) + carry;
                carry = (prod - (prod % 10)) / 10;
                currLine._num.insert(currLine._num.begin(), (prod % 10) + '0');
            }

            currLine._num.insert(currLine._num.begin(), carry + '0');
            if (currLine._num[0] == '0')
            {currLine._num.erase(currLine._num.begin());}

 
            
            product += currLine;
            loopCnt++;
        }

        
        temp._num = product._num;
        
        return temp;
    }
}

Whole_Num Whole_Num::_karatsuba(Whole_Num lhs, Whole_Num rhs)
{
    if (lhs.size() == 1 || rhs.size() == 1) 
    {return _mult(lhs, rhs);}
    
    else
    {
        char s = '1';
        // Sets the sign
        if (lhs.sign() == '-' xor rhs.sign() == '-')
        {s = '-';}

        else
        {s = '+';}

        // Makes their size the same
        if (lhs.size() != rhs.size())
        {
            while (lhs.size() < rhs.size())
            {lhs._num.insert(lhs._num.begin(), '0');}

            while (lhs.size() > rhs.size())
            {rhs._num.insert(rhs._num.begin(), '0');}
        }

        size_t n = lhs.size();
        size_t half = n / 2;

        size_t acLen = 0;

        if (n % 2 == 0)
        {acLen = half;}

        else
        {acLen = half + 1;}

        // Creating 'a' and 'c'
        Whole_Num a = "0"; a._num.clear(); a._sign = '+';
        Whole_Num c = "0"; c._num.clear(); c._sign = '+';

        for (size_t i = 0; i < acLen; i++)
        {
            a._num.push_back(lhs._num[i]);
            c._num.push_back(rhs._num[i]);
        }

        while (a._num[0] == '0' && a.size() > 1)
        {a._num.erase(a._num.begin());}

        if (a._num[0] == '0' && a.size() == 1)
        {a._sign = '?';}

        while (c._num[0] == '0' && c.size() > 1)
        {c._num.erase(c._num.begin());}

        if (c._num[0] == '0' && c.size() == 1)
        {c._sign = '?';}


        // Creating 'b' and 'd'
        Whole_Num b = "0"; b._num.clear(); b._sign = '+';
        Whole_Num d = "0"; d._num.clear(); d._sign = '+';
        
       

        for (size_t i = acLen; i < n; i++)
        {
            b._num.push_back(lhs._num[i]);
            d._num.push_back(rhs._num[i]);
        }

        while (b._num[0] == '0' && b.size() > 1)
        {b._num.erase(b._num.begin());}

        if (b._num[0] == '0' && b.size() == 1)
        {b._sign = '?';}

        while (d._num[0] == '0' && d.size() > 1)
        {d._num.erase(d._num.begin());}

        if (d._num[0] == '0' && d.size() == 1)
        {d._sign = '?';}


        Whole_Num ac = _karatsuba(a, c);
        Whole_Num bd = _karatsuba(b, d);

        Whole_Num ad_plus_bc = _karatsuba(a, d) + _karatsuba(b, c);

        Whole_Num s1 = "1";
        for (size_t i = 0; i < 2 * half; i++)
        {ac._num.push_back('0');}

        Whole_Num s2 = "1";
        for (size_t i = 0; i < half; i++)
        {ad_plus_bc._num.push_back('0');}

        Whole_Num result = ac + ad_plus_bc + bd;
        result._sign = s;
        return result;
    }

    return "0";
}

Whole_Num Whole_Num::_exp(Whole_Num lhs, Whole_Num rhs)
{
    // if either are zero
    if (lhs == "0" || rhs == "0")
    {
        // if only lhs is zero
        if (lhs == "0" && rhs != "0")
        {
            if (rhs > "0")
            {return "0";}

            else
            {throw std::invalid_argument("Division by zero is undefined");}
        }

        // if only rhs is zero
        else if (lhs != "0" && rhs == "0")
        {
            if (lhs > "0")
            {return "1";}

            else
            {return "0";}
        }

        // if both are zero
        else
        {throw std::invalid_argument("Zero to the zero power is undefined");}
    }

    // Ones
    else if (lhs == "1" || rhs == "1")
    {return lhs;}

    // Negative
    else if (rhs < "0")
    {throw std::invalid_argument("Not yet");}

    // Positives
    else
    {
        Whole_Num temp = lhs;
        for (Whole_Num i = "1"; i < rhs; i++)
        {temp *= lhs;}

        return temp;
    }
    
    
    return "0";
}

Whole_Num Whole_Num::_factorial(Whole_Num n)
{
    if (n < "0")
    {throw std::invalid_argument("Cannot be less than zero");}

    else if (n == "0" || n == "1")
    {return "1";}

    else
    {return n * _factorial(n - "1");}
}

Whole_Num Whole_Num::_div(Whole_Num lhs, Whole_Num rhs)
{
    // if either are 0
    if (lhs == "0" || rhs == "0")
    {
        // (lhs = 0), (rhs = -, -1, 1, +)
        if (lhs == "0" && rhs != "0")
        {return lhs;}

        // (lhs = -, -1, 0, 1, +), (rhs = 0)
        else
        {throw std::invalid_argument("Division by zero is undefined");}
    }

    // if either are 1
    else if (lhs == "1" || rhs == "1")
    {
        // (lhs = -, -1, 1, +), (rhs = 1)
        if (rhs == "1")
        {return lhs;}

        // (lhs = 1), (rhs = -, -1, +)
        else
        {
            if (rhs == "-1")
            {return rhs;}

            else
            {return "0";}
        }
    }

    // if either are -1
    else if (lhs == "-1" || rhs == "-1")
    {
        // (lhs = -1), (rhs = -1)
        if (lhs == "-1" && rhs == "-1")
        {return "1";}

        // (lhs = -1), (rhs = -, +)
        else if (lhs == "-1")
        {return "0";}

        // if (lhs = -, +), (rhs = -1)
        else
        {
            Whole_Num temp = lhs;
            
            if (temp.sign() == '-')
            {temp._sign = '+';}

            else
            {temp._sign = '-';}

            return temp;
        }
    }

    // (lhs = -, +), (rhs = -, +)
    else
    {
        Whole_Num quotient = "0";

        if (lhs.sign() == '-' xor rhs.sign() == '-')
        {quotient._sign = '-';}

        else
        {quotient._sign = '+';}

        Whole_Num dividend = lhs.abs();
        Whole_Num divisor = rhs.abs();

        // if they are the same number
        if (dividend == divisor)
        {
            quotient._num = {'1'};
            return quotient;
        }

        // if lhs is less than rhs
        else if (dividend < divisor)
        {return "0";}

        // if lhs is greater than rhs
        else
        {
            quotient._num.clear();
            Whole_Num remainder = "0";

            // perform regular division
            for (size_t i = 0; i < dividend.size(); i++)
            {
        
                // Adds number to end of remainder
                if (remainder != "0")
                {remainder._num.push_back(dividend._num[i]);}

                else
                {
                    if (dividend._num[i] != '0')
                    {
                        remainder._num.clear();
                        remainder._sign = '+';
                        remainder._num.push_back(dividend._num[i]);
                    }
                }
                

                // if carry is smaller than rhs
                if (remainder < divisor)
                {quotient._num.push_back('0');}

                // takes away from carry
                else
                {
                    char digit = '1';
                    Whole_Num diff = divisor;
                    while (diff + divisor <= remainder)
                    {
                        digit += 1;
                        diff += divisor;
                    }

                    remainder -= diff;
                    
                    quotient._num.push_back(digit);
                }
            }

            while (quotient._num[0] == '0')
            {quotient._num.erase(quotient._num.begin());}

            return quotient;
        }
    }

    return "0";
}

Whole_Num Whole_Num::_mod(Whole_Num lhs, Whole_Num rhs)
{
    // Checks mod value validity
    if (rhs <= "0")
    {throw std::invalid_argument("Mod value cannot be less than or equal to zero");}

    Whole_Num congruent = "0";

    // Regular mod with positives
    if (lhs >= "0")
    {congruent = lhs - (rhs * (lhs / rhs));}

    // Mod with negatives
    else
    {congruent = rhs - _mod(lhs.abs(), rhs);}

    return congruent;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------

// Default Constructor
Whole_Num::Whole_Num(): _num({'0'}), _sign('?')
{}

// Destructor
Whole_Num::~Whole_Num()
{}

// Copy Constructor
Whole_Num::Whole_Num(const Whole_Num& other): _num(other._num), _sign(other._sign)
{}

// Move Constructor
Whole_Num::Whole_Num(Whole_Num&& other) noexcept: _num(std::move(other._num)), _sign(std::move(other._sign))
{
    other._num = {'0'};
    other._sign = '?';
}

// C-String Constructor
Whole_Num::Whole_Num(const char* s): _num(vector<char>()), _sign('?')
{
    size_t i = 0;

    if (s[i] == '+' || s[i] == '-')
    {
        _sign = s[i];
        i++;
    }

    
    bool stillZero = true;
    while (s[i] != '\0')
    {
        if (stillZero)
        {
            if (s[i] != '0')
            {stillZero = false;}
        }

        if (!stillZero)
        {
            if (int(s[i]) < 48 || int(s[i]) > 57)
            {throw std::invalid_argument("Needs to be valid number");}
            _num.push_back(s[i]);
        }

        i++;
    }

    
    if (_sign == '?' && _num != vector<char>(1, 0))
    {_sign = '+';}

    if (_num.empty())
    {
        _num.push_back('0');
        _sign = '?';
    }

}

// Char Constructor
Whole_Num::Whole_Num(const char c): _num(vector<char>()), _sign('+')
{
    // Checks if c is valid
    if ((int)c < 48 || (int)c > 57)
    {throw std::invalid_argument("Needs a digit");}

    _num.push_back(c);
    if (c == '0')
    {_sign = '?';}
}

// Copy Assignment Operator
Whole_Num &Whole_Num::operator=(const Whole_Num& other) 
{
    if (this != &other)
    {
        _num = other._num;
        _sign = other._sign;
    }

    return *this;
}

// Move Assignment Operator
Whole_Num &Whole_Num::operator=(Whole_Num&& other) noexcept
{
    if (this != &other)
    {
        _num = other._num;
        _sign = other._sign;
        other._num = {'0'};
        other._sign = '?';
    }

    return *this;
}


//--------------------------------------------------------------------------------------------------------------------------------------------------------


// sign
char Whole_Num::sign() const
{return _sign;}

// at
const char& Whole_Num::at(size_t pos) const
{return _num.at(pos);}

// size
size_t Whole_Num::size() const
{return _num.size();}

// absolute value
Whole_Num Whole_Num::abs() const
{
    Whole_Num temp = *this;

    if (_sign == '-')
    {temp._sign = '+';}
    
    return temp;
}


//--------------------------------------------------------------------------------------------------------------------------------------------------------

// +=
Whole_Num &Whole_Num::operator+=(const Whole_Num& rhs)
{
    Whole_Num temp = "0";

    // If the signs are the same or at least one of them is zero
    if ((_sign == rhs.sign()) || (_sign == '?' || rhs.sign() == '?'))
    {temp = _add(*this, rhs);}

    // If the signs are opposite (+,-)
    else
    {temp = _sub(*this, rhs);}


    *this = temp;
    return *this;
}

// -=
Whole_Num &Whole_Num::operator-=(const Whole_Num& rhs)
{
    Whole_Num temp = rhs;
    
    if (temp._sign == '-')
    {temp._sign = '+';}

    else if (temp._sign ==  '+')
    {temp._sign = '-';}

    *this += temp;
   

    return *this;
}

// *=
Whole_Num &Whole_Num::operator*=(const Whole_Num& rhs)
{

    *this = _karatsuba(*this, rhs);
    return *this;
}

// ^=
Whole_Num &Whole_Num::operator^=(const Whole_Num& rhs)
{
    *this = _exp(*this, rhs);
    return *this;
}

// /=
Whole_Num &Whole_Num::operator/=(const Whole_Num& rhs)
{
    *this = _div(*this, rhs);
    return *this;
}

// %=
Whole_Num &Whole_Num::operator%=(const Whole_Num& rhs)
{
    *this = _mod(*this, rhs);
    return *this;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------

// +
Whole_Num operator+(Whole_Num lhs, const Whole_Num& rhs)
{
    lhs += rhs; 
    return lhs; 
}

// -
Whole_Num operator-(Whole_Num lhs, const Whole_Num& rhs)
{
    lhs -= rhs; 
    return lhs; 
}

// *
Whole_Num operator*(Whole_Num lhs, const Whole_Num& rhs)
{
    lhs *= rhs; 
    return lhs; 
}

// ^
Whole_Num operator^(Whole_Num lhs, const Whole_Num& rhs)
{
    lhs ^= rhs; 
    return lhs; 
}

// /
Whole_Num operator/(Whole_Num lhs, const Whole_Num& rhs)
{
    lhs /= rhs; 
    return lhs; 
}

// %
Whole_Num operator%(Whole_Num lhs, const Whole_Num& rhs)
{
    lhs %= rhs; 
    return lhs; 
}


//--------------------------------------------------------------------------------------------------------------------------------------------------------

// pre-increment operator 
Whole_Num& Whole_Num::operator++()
{
    // if it is -1
    if (*this == "-1")
    {
        _num[0] = '0';
        _sign = '?';
    }

    // if it is 0
    else if (*this == "0")
    {
        _num[0] = '1';
        _sign = '+';
    }

    // if it is positive
    else if (_sign == '+')
    {_incNum();}

    // if it is negative
    else if (_sign == '-')
    {_decNum();}


    return *this;
}

// post-increment operator
Whole_Num Whole_Num::operator++(int)
{
    Whole_Num temp = *this;
    ++(*this);
    return temp;
}

// pre-decrement operator
Whole_Num& Whole_Num::operator--()
{
    // if it is 1
    if (*this == "1")
    {
        _num[0] = '0';
        _sign = '?';
    }

    // if it is 0
    else if (*this == "0")
    {
        _num[0] = '1';
        _sign = '-';
    }

    // if it is negative
    else if (_sign == '-')
    {_incNum();}

    // if it is positive
    else if (_sign == '+')
    {_decNum();}

    return *this;
}

// post-decrement operator
Whole_Num Whole_Num::operator--(int)
{
    Whole_Num temp = *this;
    --(*this);
    return temp;
}


//--------------------------------------------------------------------------------------------------------------------------------------------------------


// <
bool Whole_Num::operator<(const Whole_Num& rhs) const
{
    // if they are the same signs
    if (_sign == rhs._sign)
    {
        
        // if they're both zeros
        if(_sign == '?' && rhs._sign == '?')
        {return false;}

        // if they're other numbers
        else
        {
            // if lhs and rhs are unequal
            if (size() != rhs.size())
            {
                if (_sign == '+')
                {return size() < rhs.size();}

                else if (_sign == '-')
                {return size() > rhs.size();}
            }


            // if lhs and rhs are equal
            else
            {
                
                // if numbers are positive
                if (_sign == '+')
                {
                    for (size_t i = 0; i < size(); i++)
                    {
                        if (_num[i] != rhs._num[i])
                        {return _num[i] < rhs._num[i];}
                    }
                    return false;
                }

                // if numbers are negative
                else if (_sign == '-')
                {
                    
                    for (size_t i = 0; i < size(); i++)
                    {
                        if (_num[i] != rhs._num[i])
                        {return _num[i] > rhs._num[i];}
                    }
                    return false;
                }
            }
        }
    }


    // if they are different signs
    else
    {
        if (_sign == '+')
        {return false;}

        else if (_sign == '-')
        {return true;}

        else
        {
            if (_sign == '?' && rhs._sign == '-')
            {return false;}

            else if (_sign == '?' && rhs._sign == '+')
            {return true;}
        }
    }

    return 0;
}

// >
bool Whole_Num::operator>(const Whole_Num& rhs) const
{return rhs < *this;}

// <=
bool Whole_Num::operator<=(const Whole_Num& rhs) const
{return (*this < rhs) || (*this == rhs);}

// >=
bool Whole_Num::operator>=(const Whole_Num& rhs) const
{return (*this > rhs) || (*this == rhs);}

// ==
bool Whole_Num::operator==(const Whole_Num& rhs) const
{return ((*this < rhs) == false) && ((*this > rhs) == false);}

// !=
bool Whole_Num::operator!=(const Whole_Num& rhs) const
{return !(*this == rhs);}

// !
Whole_Num Whole_Num::operator!() 
{
    *this = _factorial(*this);
    return *this;
}


// output
std::ostream& operator<<(std::ostream& os, const Whole_Num& num)
{
    if (num.sign() == '-')
    {os << num.sign();}

    for (size_t i = 0; i < num.size(); i++)
    {os << num.at(i);}

    return os;
}


