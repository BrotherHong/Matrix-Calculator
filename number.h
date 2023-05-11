#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>
using namespace std;

class Fraction {
    public:
    Fraction(int numerator, int denominator);
    Fraction();

    static Fraction reciprocol(const Fraction &frac);

    Fraction operator+(const Fraction &other) const;
    Fraction operator-(const Fraction &other) const;
    Fraction operator*(const Fraction &other) const;
    Fraction operator/(const Fraction &other) const;

    void operator+=(const Fraction &other);
    void operator-=(const Fraction &other);
    void operator*=(const Fraction &other);
    void operator/=(const Fraction &other);

    bool operator==(const Fraction &other) const;
    bool operator<(const Fraction &other) const;
    bool operator>(const Fraction &other) const;
    bool operator<=(const Fraction &other) const;
    bool operator>=(const Fraction &other) const;

    friend Fraction operator-(const Fraction &frac);

    friend ostream& operator<<(ostream &os, Fraction &frac);
    friend istream& operator>>(istream &is, Fraction &frac);

    friend class Integer;

    private:
    int numerator;
    int denominator;
};

class Integer : public Fraction {
    public:
    explicit Integer(int num);
    Integer();

    Integer operator%(Integer &other);
    void operator%=(Integer &other);
};

#endif