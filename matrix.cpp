#include "matrix.h"
#include <iomanip>
#include <cmath>

Matrix::Matrix(int m, int n) : row(m), col(n) {
    mat = new Fraction*[m];
    for (int i = 0;i < row;i++) {
        mat[i] = new Fraction[n];
    }
}

Matrix::Matrix(int n) : Matrix(n, n) {}

Matrix::Matrix(const Matrix &matrix) : row(matrix.row), col(matrix.col) {
    for (int i = 0;i < row;i++) {
        for (int j = 0;j < col;j++) {
            mat[i][j] = matrix.mat[i][j];
        }
    }
}

Matrix::~Matrix() {
    for (int i = 0;i < row;i++) {
        delete [] mat[i];
    }
    delete [] mat;
}

Matrix Matrix::identity(int n) {
    Matrix res(n);
    for (int i = 0;i < n;i++) {
        res.mat[i][i] = Integer(1);
    }
    return res;
}

Matrix Matrix::operator+(const Matrix &other) const {
    if (row != other.row || col != other.col) {
        cerr << "Error occuring while doing + operation on Matrix" << endl;
        exit(EXIT_SUCCESS);
    }
    Matrix res(row, col);
    for (int i = 0;i < row;i++) {
        for (int j = 0;j < col;j++) {
            res.mat[i][j] = mat[i][j] + other.mat[i][j];
        }
    }
    return res;
}

Matrix Matrix::operator-(const Matrix &other) const {
    return (*this) + (Integer(-1) * other);
}

Matrix Matrix::operator*(const Matrix &other) const {
    if (col != other.row) {
        cerr << "Error occuring while doing * operation on Matrix" << endl;
        exit(EXIT_SUCCESS);
    }
    Matrix res(row, other.col);
    for (int i = 0;i < row;i++) {
        for (int j = 0;j < other.col;j++) {
            for (int k = 0;k < col;k++) {
                res.mat[i][j] += res.mat[i][k] * res.mat[k][j];
            }
        }
    }
    return res;
}

Matrix Matrix::operator*(Fraction multiplier) const {
    Matrix res(row, col);
    for (int i = 0;i < row;i++) {
        for (int j = 0;j < col;j++) {
            res.mat[i][j] = multiplier * mat[i][j];
        }
    }
    return res;
}

Matrix operator*(const Fraction multiplier, const Matrix &matrix) {
    return (matrix * multiplier);
}

Matrix Matrix::inverse() const {
    Fraction det = determinant();
    if (det == Integer(0)) {
        cerr << "This matrix does not have inversion" << endl;
        exit(EXIT_SUCCESS);
    }
    return Fraction::reciprocol(det) * adjoint();
}

Matrix Matrix::transpose() const {
    Matrix res(col, row);
    for (int i = 0;i < col;i++) {
        for (int j = 0;j < row;j++) {
            res.mat[i][j] = mat[j][i];
        }
    }
    return res;
}

Matrix Matrix::adjoint() const {
    Matrix adj(row, col);
    for (int i = 0;i < row;i++) {
        for (int j = 0;j < col;j++) {
            adj.mat[i][j] = cofactor(i, j);
        }
    }
    return adj.transpose();
}

Fraction Matrix::determinant() const {
    if (row != col) {
        cerr << "Error occuring while calculating determinant" << endl;
        exit(EXIT_SUCCESS);
    }
    if (row == 1) {
        return mat[0][0];
    }
    Fraction res = Integer(0);
    for (int i = 0;i < row;i++) {
        res += mat[i][0] * cofactor(i, 0);
    }
    return res;
}

Fraction Matrix::cofactor(int r, int c) const {
    if (row != col) {
        cerr << "Error occuring while calculating cofactor" << endl;
        exit(EXIT_SUCCESS);
    }

    Fraction res = ((r+c)%2 == 0 ? Integer(1) : Integer(-1));
    Matrix M(row-1, col-1);

    for (int i = 0;i < row;i++) {
        for (int j = 0;j < col;j++) {
            if (i == r || j == c) continue;
            int rr = i + (i < r ? 0 : -1);
            int cc = j + (j < c ? 0 : -1);
            M.mat[rr][cc] = mat[i][j];
        }
    }
    return res * M.determinant();
}

bool Matrix::hasInverse() const {
    return (determinant() == Integer(0) ? false : true);
}

ostream& operator<<(ostream &os, Matrix &matrix) {
    for (int i = 0;i < matrix.row;i++) {
        for (int j = 0;j < matrix.col;j++) {
            os << setw(6) << setfill(' ') << matrix.mat[i][j];
        }
        os << endl;
    }
    return os;
}

istream& operator>>(istream &is, Matrix &matrix) {
    cout << "Please input " << matrix.row << "x" << matrix.col << " matrix:" << endl;
    for (int i = 0;i < matrix.row;i++) {
        for (int j = 0;j < matrix.col;j++) {
            is >> matrix.mat[i][j];
        }
    }
    return is;
}
