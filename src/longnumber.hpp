#include <bits/stdc++.h>

class LongNumber {

	bool positive = 1;
    int exp = 0;
	std::vector <char> digits;

public:

	LongNumber() = default; // constructor
    LongNumber(const LongNumber&) = default; // copy constructor
    ~LongNumber() = default; // destructor

	LongNumber& operator=(const LongNumber&) = default; // copy assignment

	LongNumber(long double value);

	friend int precision(LongNumber& lhs);
    friend void set_precision(LongNumber& lhs, int precision);

    friend void normalize(LongNumber& lhs, LongNumber& rhs);
    friend void clearzeros(LongNumber& lhs);

    friend bool operator ==(LongNumber lhs, LongNumber rhs);
    friend bool operator !=(LongNumber lhs, LongNumber rhs);

    friend LongNumber operator +(LongNumber lhs, LongNumber rhs);

    friend LongNumber operator -(const LongNumber& value);
    friend LongNumber operator -(LongNumber lhs, LongNumber rhs);

    friend bool operator <(LongNumber lhs, LongNumber rhs);
    friend bool operator >(LongNumber lhs, LongNumber rhs);
    friend bool operator <=(LongNumber lhs, LongNumber rhs);
    friend bool operator >=(LongNumber lhs, LongNumber rhs);
    
    friend LongNumber operator *(LongNumber lhs, LongNumber rhs);

    friend LongNumber operator /(LongNumber lhs, LongNumber rhs);

    friend std::ostream& operator <<(std::ostream& out, const LongNumber& num);
};

LongNumber operator""_LongNumber(long double val);
