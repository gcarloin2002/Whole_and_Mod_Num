#ifndef WHOLE_NUM_H
#define WHOLE_NUM_H

#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;


class Whole_Num
{
    private:
        vector<char> _num;
        char _sign;

    private:
        void _incNum();
        void _decNum();
        Whole_Num _add(Whole_Num lhs, Whole_Num rhs);
        Whole_Num _sub(Whole_Num lhs, Whole_Num rhs);
        Whole_Num _mult(Whole_Num lhs, Whole_Num rhs);
        Whole_Num _karatsuba(Whole_Num lhs, Whole_Num rhs);
        Whole_Num _exp(Whole_Num lhs, Whole_Num rhs);
        Whole_Num _factorial(Whole_Num n);
        Whole_Num _div(Whole_Num lhs, Whole_Num rhs);
        Whole_Num _mod(Whole_Num lhs, Whole_Num rhs);

    public:
        Whole_Num(); // Default Constructor
        ~Whole_Num(); // Destructor
        Whole_Num(const Whole_Num& other); // Copy Constructor
        Whole_Num(Whole_Num&& other) noexcept; // Move Constructor
        Whole_Num(const char* s); // C-String Constructor
        Whole_Num(const string s); // String Constructor
        Whole_Num(const char c); // Char Constructor
        Whole_Num& operator=(const Whole_Num& other); // Copy Assignment Operator
        Whole_Num& operator=(Whole_Num&& other) noexcept; // Move Assignment Operator

        char sign() const; // sign
        const char& at(size_t pos) const; // at
        size_t size() const; // size
        Whole_Num abs() const; // absolute value

        Whole_Num& operator++(); // ++x
        Whole_Num operator++(int); // x++
        Whole_Num& operator--(); // --x
        Whole_Num operator--(int); // x--

        Whole_Num& operator+=(const Whole_Num& rhs); // +=
        Whole_Num& operator-=(const Whole_Num& rhs); // -=
        Whole_Num& operator*=(const Whole_Num& rhs); // *=
        Whole_Num& operator^=(const Whole_Num& rhs); // ^=
        Whole_Num& operator/=(const Whole_Num& rhs); // /=
        Whole_Num& operator%=(const Whole_Num& rhs); // %=

        friend Whole_Num operator+(Whole_Num lhs, const Whole_Num& rhs); // +
        friend Whole_Num operator-(Whole_Num lhs, const Whole_Num& rhs); // -
        friend Whole_Num operator*(Whole_Num lhs, const Whole_Num& rhs); // *
        friend Whole_Num operator^(Whole_Num lhs, const Whole_Num& rhs); // ^
        friend Whole_Num operator/(Whole_Num lhs, const Whole_Num& rhs); // /
        friend Whole_Num operator%(Whole_Num lhs, const Whole_Num& rhs); // /

        bool operator<(const Whole_Num& rhs) const; // <
        bool operator>(const Whole_Num& rhs) const; // >
        bool operator<=(const Whole_Num& rhs) const; // <=
        bool operator>=(const Whole_Num& rhs) const; // >=
        bool operator==(const Whole_Num& rhs) const; // ==
        bool operator!=(const Whole_Num& rhs) const; // !=
        Whole_Num operator!(); // !

      
        friend std::ostream& operator<<(std::ostream& os, const Whole_Num& num); // output
};





#endif