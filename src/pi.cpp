#include "longnumber.cpp"
#include <bits/stdc++.h>

using namespace std;

LongNumber getpi(int precision = 100) {
	LongNumber current = LongNumber(2);
    LongNumber res = current;
    set_precision(res, precision + 10); set_precision(current, precision + 10);
    LongNumber two = LongNumber(2); set_precision(two, precision + 10);
    for (int i = 1; i <= precision * 5; ++i) {
        current = current / two;
        current = current * i * two;
        current = current / (i * two + 1);
        res = res + current;
    }
    set_precision(res, precision);
    return res;
}
