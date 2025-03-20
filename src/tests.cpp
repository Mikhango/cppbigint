#include "longnumber.cpp"
#include <bits/stdc++.h>

using namespace std;

string first_test() {
    LongNumber ans = LongNumber(0);
    int intans = 0;
    for (int i = 0; i < 100; ++i) {
        intans += i;
        ans = ans + LongNumber(i);
    }
    if (ans < LongNumber(100000) && ans > LongNumber(0) && ans == LongNumber(intans)) return "OK";
    return "FAIL";
}

string second_test() {
    LongNumber ans = LongNumber(1);
    int intans = 1;
    for (int i = 1; i <= 10; ++i) {
        intans *= i;
        ans = ans * LongNumber(i);
    }
    if (ans != LongNumber(100000) && ans > LongNumber(0) && ans == LongNumber(intans)) return "OK";
    return "FAIL";
}

string third_test() {
    LongNumber ans = LongNumber(1);
    long double ldans = 1;
    for (int i = 1; i < 10; ++i) {
        ldans /= 2;
        ans = ans / 2;
    }
    if (ans < LongNumber(100000) && ans == LongNumber(ldans)) return "OK";
    return "FAIL";
}

string fourth_test() {
    LongNumber ans = LongNumber(0);
    int intans = 0;
    for (int i = 1; i < 10; ++i) {
        intans = intans * i + intans;
        ans = ans + i * ans;
    }
    if (ans == LongNumber(intans)) return "OK";
    return "FAIL";
}

string fifth_test() {
    LongNumber ans = LongNumber(0);
    int intans = 0;
    for (int i = 1; i < 10; ++i) {
        intans = intans * i + intans + i;
        ans = ans + i * ans + i;
    }
    if (ans == LongNumber(intans)) return "OK";
    return "FAIL";
}

signed main() {
    cout << first_test() << endl;
    cout << second_test() << endl;
    cout << third_test() << endl;
    cout << fourth_test() << endl;
    cout << fifth_test() << endl;
}