#ifndef MATRIX_H
#define MATRIX_H

#include "number.h"
using namespace std;

class Matrix {
    public:
    Matrix(int m, int n);
    Matrix(int n);
    Matrix(const Matrix &matrix);
    ~Matrix();

    static Matrix identity(int n);

    Matrix operator+(const Matrix &other) const;
    Matrix operator-(const Matrix &other) const;
    Matrix operator*(const Matrix &other) const;
    Matrix operator*(const Fraction multiplier) const;
    friend Matrix operator*(const Fraction multiplier, const Matrix &matrix);

    Matrix inverse() const;
    Matrix transpose() const;
    Matrix adjoint() const;
    Fraction determinant() const;
    Fraction cofactor(int r, int c) const;
    bool hasInverse() const;


    friend ostream& operator<<(ostream &os, Matrix &matrix);
    friend istream& operator>>(istream &is, Matrix &matrix);

    private:
    int row, col;
    Fraction **mat;
};

#endif