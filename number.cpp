#include "number.h"
#include <numeric>
#include <string>

Fraction::Fraction(int num, int denom) {
    if (denom == 0) {
        cerr << "Error occuring while constructing Fraction" << endl;
        exit(EXIT_SUCCESS);
    }
    int g = gcd(num, denom);
    numerator = num / g;
    denominator = denom / g;
    if (numerator <= 0 && denominator <= 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
}

Fraction::Fraction() : Fraction(0, 1) {}

Fraction Fraction::reciprocol(const Fraction &frac) {
    if (frac.numerator == 0) {
        cerr << "Error occuring while getting reciprocol" << endl;
        exit(EXIT_SUCCESS);
    }
    return Fraction(frac.denominator, frac.numerator);
}

Fraction Fraction::operator+(const Fraction &other) const {
    int num = numerator * other.denominator + other.numerator * denominator;
    int denom = denominator * other.denominator;
    return Fraction(num, denom);
}

Fraction Fraction::operator-(const Fraction &other) const {
    return (*this) + (-other);
}

Fraction Fraction::operator*(const Fraction &other) const {
    int num = numerator * other.numerator;
    int denom = denominator * other.denominator;
    return Fraction(num, denom);
}

Fraction Fraction::operator/(const Fraction &other) const {
    return (*this) * Fraction::reciprocol(other);
}

void Fraction::operator+=(const Fraction &other) {
    (*this) = (*this) + other;
}

void Fraction::operator-=(const Fraction &other) {
    (*this) = (*this) - other;
}

void Fraction::operator*=(const Fraction &other) {
    (*this) = (*this) * other;
}

void Fraction::operator/=(const Fraction &other) {
    (*this) = (*this) / other;
}

bool Fraction::operator==(const Fraction &other) const {
    return (numerator == other.numerator && denominator == other.denominator);
}

bool Fraction::operator<(const Fraction &other) const {
    int num1 = numerator * other.denominator;
    int num2 = other.numerator * denominator;
    return (num1 < num2);
}

bool Fraction::operator>(const Fraction &other) const {
    return !((*this) <= other);
}

bool Fraction::operator<=(const Fraction &other) const {
    return ((*this) < other) || ((*this) == other);
}

bool Fraction::operator>=(const Fraction &other) const {
    return !((*this) < other);
}

Fraction operator-(const Fraction &frac) {
    return (Integer(-1) * frac);
}

ostream& operator<<(ostream &os, Fraction &frac) {
    if (frac.denominator == 1) {
        os << frac.numerator;
    } else {
        os << frac.numerator << '/' << frac.denominator;
    }
    return os;
}

istream& operator>>(istream &is, Fraction &frac) {
    string str;
    is >> str;
    if (str.find('/') == string::npos) {
        frac = Integer(stoi(str));
    } else {
        int cutIdx = 0;
        while (str[cutIdx] != '/') cutIdx++;
        int num = stoi(str.substr(0, cutIdx));
        int denom = stoi(str.substr(cutIdx+1));
        frac = Fraction(num, denom);
    }
    return is;
}

Integer::Integer(int num) : Fraction(num, 1) {}

Integer::Integer() : Integer(0) {}

Integer Integer::operator%(Integer &other) {
    return Integer(numerator % other.numerator);
}

void Integer::operator%=(Integer &other) {
    numerator %= other.numerator;
}
