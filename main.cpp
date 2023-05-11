#include <iostream>
#include "matrix.h"
#include "number.h"
using namespace std;

int main() {
    int m, n;
    cout << "Input m x n: ";
    cin >> m >> n;

    Matrix mat(m, n);
    cin >> mat;

    cout << "Matrix: " << endl;
    cout << mat << endl;

    Fraction determinant = mat.determinant();
    cout << "Determinant: " << determinant << endl;

    Matrix adjoint = mat.adjoint();
    cout << "Adjoint: " << endl;
    cout << adjoint << endl;

    if (mat.hasInverse()) {
        Matrix inverse = mat.inverse();
        cout << "Inverse: " << endl;
        cout << inverse << endl;
    } else {
        cout << "This matrix does not have inverse." << endl;
    }

    return 0;
}