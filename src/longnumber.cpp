#include "longnumber.hpp"
#include <bits/stdc++.h>

using namespace std;

pair <char, char> addbit(char a, char b, char c) {
    int cnttrue = (a == '1') + (b == '1') + (c == '1');
    if (cnttrue == 3) return {'1', '1'};
    if (cnttrue == 2) return {'0', '1'};
    if (cnttrue == 1) return {'1', '0'};
    return {'0', '0'};
}

void normalize(LongNumber& lhs, LongNumber& rhs) {
    while (lhs.exp < rhs.exp) {
        ++lhs.exp;
        lhs.digits.push_back('0');
    }
    while (lhs.exp > rhs.exp) {
        ++rhs.exp;
        rhs.digits.push_back('0');
    }
    int delta = abs((int) lhs.digits.size() - (int) rhs.digits.size());
    if (lhs.digits.size() < rhs.digits.size()) {
        reverse(lhs.digits.begin(), lhs.digits.end());
        for (int i = 0; i < delta; ++i) lhs.digits.push_back('0');
        reverse(lhs.digits.begin(), lhs.digits.end());
    } else {
        reverse(rhs.digits.begin(), rhs.digits.end());
        for (int i = 0; i < delta; ++i) rhs.digits.push_back('0');
        reverse(rhs.digits.begin(), rhs.digits.end());
    }
}

int precision(LongNumber& lhs) {
    return (int) lhs.digits.size() - lhs.exp;
}

void set_precision(LongNumber& lhs, int nprecision) {
    int current = precision(lhs);
    int delta = abs(nprecision - current);
    reverse(lhs.digits.begin(), lhs.digits.end());
    if (nprecision > current) {
        for (int i = 0; i < delta; ++i) lhs.digits.push_back('0');
    } else {
        for (int i = 0; i < delta; ++i) lhs.digits.pop_back();
    }
    reverse(lhs.digits.begin(), lhs.digits.end());
}

void clearzeros(LongNumber& lhs) {
    if (lhs.exp == 0) {
        lhs.digits.push_back('0');
        ++lhs.exp;
    }
    while (lhs.exp > 1) {
        if (lhs.digits.back() == '0') {
            lhs.digits.pop_back();
            --lhs.exp;
        } else {
            break;
        }
    }
}

LongNumber::LongNumber(long double value) {
    positive = (value >= 0);
    long double number = frexp(value, &exp);
    long long curr = number * (((long long) 1) << 62);
    for (int i = 0; i < 62; ++i) {
        digits.push_back(curr % 2 == 0 ? '0' : '1');
        curr /= 2;
    }
    if (exp == 0) {digits.push_back('0'); ++exp;}
    // reverse(digits.begin(), digits.end());
}

LongNumber operator+(LongNumber lhs, LongNumber rhs) {
    // cout << "SSUM" << endl;
    set_precision(rhs, precision(lhs));
    if (lhs.positive != rhs.positive) {
        if (lhs.positive) {
            rhs.positive = !rhs.positive;
            return lhs - rhs;
        } else {
            lhs.positive = !lhs.positive;
            return rhs - lhs;
        }
    }
    while (lhs.exp < rhs.exp) {
        ++lhs.exp;
        lhs.digits.push_back('0');
    }
    while (lhs.exp > rhs.exp) {
        ++rhs.exp;
        rhs.digits.push_back('0');
    }
    // cout << lhs << endl << rhs << endl;
    char nextbit = '0';
    LongNumber summary = lhs;
    // cout << summary << endl;
    for (int i = 0; i < lhs.digits.size(); ++i) {
        pair <char, char> currbits = addbit(nextbit, lhs.digits[i], rhs.digits[i]);
        summary.digits[i] = currbits.first;
        nextbit = currbits.second;
    }
    if (nextbit == '1') {summary.digits.push_back('1'); ++summary.exp;}
    /*cout << summary << endl;
    cout << "ESUM" << endl;*/
    return summary;
}

LongNumber operator-(const LongNumber& value) {
    LongNumber val = value;
    val.positive = !val.positive;
    return val;
}

LongNumber operator-(LongNumber lhs, LongNumber rhs) {
    set_precision(rhs, precision(lhs));
    if (lhs.positive != rhs.positive) return lhs + (-rhs);
    while (lhs.exp < rhs.exp) {
        ++lhs.exp;
        lhs.digits.push_back('0');
    }
    while (lhs.exp > rhs.exp) {
        ++rhs.exp;
        rhs.digits.push_back('0');
    }
    LongNumber summary = lhs;
    if (lhs < rhs) {
        swap(lhs, rhs);
        summary.positive = !lhs.positive;
    }
    bool getnxtbit = 0;
    for (int i = 0; i < lhs.digits.size(); ++i) {
        if (getnxtbit && lhs.digits[i] == '1') {
            lhs.digits[i] = '0';
            getnxtbit = 0;
        }
        if (lhs.digits[i] == rhs.digits[i]) {
            if (getnxtbit) summary.digits[i] = '1';
            else summary.digits[i] = '0';
        } else if (lhs.digits[i] > rhs.digits[i]) {
            summary.digits[i] = '1';
        } else {
            if (getnxtbit) summary.digits[i] = '0';
            else summary.digits[i] = '1';
            getnxtbit = 1;
        }
    }
    clearzeros(summary);
    return summary;
}

LongNumber operator *(LongNumber lhs, LongNumber rhs) {
    LongNumber summary = LongNumber(0);
    set_precision(summary, precision(lhs));
    LongNumber currentstep;
    int step = rhs.digits.size();
    step = rhs.exp - step;
    for (int i = 0; i < rhs.digits.size(); ++i) {
        if (rhs.digits[i] == '0') {
            ++step;
            continue;
        }
        currentstep = lhs;
        currentstep.positive = 1;
        if (step < 0) {
            for (int j = step; j < 0; ++j) {
                --currentstep.exp;
                if (currentstep.exp == 0) {
                    ++currentstep.exp;
                    currentstep.digits.push_back('0');
                }
            }
        } else {
            reverse(currentstep.digits.begin(), currentstep.digits.end());
            for (int j = -step; j < 0; ++j) {
                ++currentstep.exp;
                if (currentstep.exp - 1 == currentstep.digits.size()) {
                    currentstep.digits.push_back('0');
                }
            }
            reverse(currentstep.digits.begin(), currentstep.digits.end());
        }
        summary = summary + currentstep;
        ++step;
    }
    if (lhs.positive != rhs.positive) summary.positive = 0;
    clearzeros(summary);
    return summary;
}

LongNumber operator /(LongNumber lhs, LongNumber rhs) {
    set_precision(rhs, precision(lhs));
    if (rhs == LongNumber(0)) {
        throw "Division by zero is not allowed";
    }
    if (lhs == LongNumber(0)) {
        return lhs;
    }
    bool sign = lhs.positive + rhs.positive;
    lhs.positive = 1; rhs.positive = 1;
    LongNumber l, r;
    if (rhs.digits.back() == '0') {
        l = LongNumber(lhs);
        r = l;
        reverse(r.digits.begin(), r.digits.end());
        for (int i = (int) rhs.digits.size() - 1; i >= 0; --i) {
            if (r.digits[i] == '1') break;
            ++r.exp;
            if (r.digits.size() == r.exp - 1) r.digits.push_back('0');
        }
        reverse(r.digits.begin(), r.digits.end());
    } else {
        l = LongNumber(0);
        r = LongNumber(lhs);
    }
    r.positive = 1; l.positive = 1;
    set_precision(l, precision(lhs));
    set_precision(r, precision(lhs));
    LongNumber zero = LongNumber(0);
    LongNumber smalldelta = zero;
    set_precision(smalldelta, precision(lhs));
    r = r + smalldelta;
    smalldelta.digits[0] = '1';
    while (l < r - smalldelta) {
        LongNumber mid = l + ((r - l) * LongNumber(0.5));
        LongNumber middiff = lhs - rhs * mid;
        LongNumber ldiff = lhs - rhs * l;
        if (ldiff <= zero) {
            if (middiff <= zero && middiff > ldiff) l = mid;
            else r = mid;
        } else {
            if (middiff >= zero && middiff < ldiff) l = mid;
            else r = mid;
        }
    }
    l.positive = sign;
    return l;
}

bool operator ==(LongNumber lhs, LongNumber rhs) {
    normalize(lhs, rhs);
    bool zeroall = 1;
    for (int i = (int) lhs.digits.size() - 1; i >= 0; --i) {
        if (!(lhs.digits[i] == rhs.digits[i])) return 0;
        zeroall &= (lhs.digits[i] == '0');
        zeroall &= (rhs.digits[i] == '0');
    }
    if (zeroall) return 1;
    if (lhs.positive == rhs.positive) return 1;
    return 0;
}

bool operator !=(LongNumber lhs, LongNumber rhs) {
    return !(lhs == rhs);
}

bool operator <(LongNumber lhs, LongNumber rhs) {
    normalize(lhs, rhs);
    bool zeroall = 1;
    for (int i = (int) lhs.digits.size() - 1; i >= 0; --i) {
        if (lhs.digits[i] < rhs.digits[i]) {
            if (rhs.positive) return 1;
            return 0;
        }
        if (lhs.digits[i] > rhs.digits[i]) {
            if (lhs.positive) return 0;
            return 1;
        }
        zeroall &= (lhs.digits[i] == '0');
        zeroall &= (rhs.digits[i] == '0');
    }
    if (zeroall) return 0;
    if (rhs.positive && !lhs.positive) return 1;
    return 0;
}

bool operator >(LongNumber lhs, LongNumber rhs) {
    return ((!(lhs < rhs)) && (lhs != rhs));
}

bool operator >=(LongNumber lhs, LongNumber rhs) {
    return !(lhs < rhs);
}

bool operator <=(LongNumber lhs, LongNumber rhs) {
    return !(lhs > rhs);
}

ostream& operator<<(std::ostream& out, const LongNumber& number) {
    if (!number.positive) out << '-';
    for (int i = ((int) number.digits.size()) - 1; i >= 0; --i) {
        out << number.digits[i];
        if (number.exp != ((int) number.digits.size()) && \
            i == ((int) number.digits.size()) - number.exp) out << '.';
    }
    return out;
}

LongNumber operator""_longnum(long double val) {
    return LongNumber(val);
};
