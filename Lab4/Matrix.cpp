//
// Created by asus on 2019/5/31.
//
#include "Matrix.h"
int Matrix::count = 0;
Matrix::Matrix(int n) {
    row = col = n;
    item = new BigNum[n * n];
}

Matrix::Matrix(int row, int col) {
    this->row = row;
    this->col = col;
    item = new BigNum[row * col];
}
Matrix::Matrix(const Matrix &matrix) {
    col = matrix.col;
    row = matrix.row;
    item = new BigNum[col * row];
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            set(i, j, matrix.get(i, j));
        }
    }

}
void Matrix::set(int i, int j, const BigNum &bigNum) const {
    item[i * col + j] = bigNum;
}

const BigNum Matrix::get(int i, int j) const {
    return item[i * col + j];
}

const Matrix Matrix::operator+(const Matrix &matrix) const {
    if (matrix.col != col || matrix.row != row) {
        cout << "Cannot add";
        assert(0);
        return *this;
    }
    Matrix _copy = *this;
    for (int i = 0; i < col * row; i++)
        _copy.item[i] = _copy.item[i] + matrix.item[i];
    return _copy;
}

Matrix& Matrix::operator+=(const Matrix &matrix) {
    if (matrix.col != col || matrix.row != row) {
        cout << "Cannot add";
        assert(0);
        return *this;
    }
    for (int i = 0; i < col * row; i++)
        item[i] = item[i] + matrix.item[i];
    return *this;
}

const Matrix Matrix::operator-(const Matrix &matrix) const {
    if (matrix.col != col || matrix.row != row) {
        cout << "Cannot reduce"  ;
        assert(0);
        return *this;
    }
    Matrix _copy = *this;
    for (int i = 0; i < col * row; i++)
        _copy.item[i] = _copy.item[i] - matrix.item[i];
    return _copy;
}

Matrix& Matrix::operator-=(const Matrix &matrix) {
    if (matrix.col != col || matrix.row != row) {
        cout << "Cannot reduce"  ;
        assert(0);
        return *this;
    }
    for (int i = 0; i < col * row; i++)
        item[i] = item[i] - matrix.item[i];
    return *this;
}

const Matrix Matrix::operator*(const int &mul) const {
    Matrix _copy = *this;
    for (int i = 0; i < col * row; i++)
        _copy.item[i] = item[i] * mul;
    return _copy;
}

const Matrix Matrix::operator*(const Matrix &matrix) const {
    if (col != matrix.row){
        cout << "Cannot multiply" ;
        assert(0);
        return *this;
    }
    Matrix _copy(row, matrix.col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < matrix.col; j++) {
            BigNum sum(0);
            for (int k = 0; k < matrix.row; k++) {
                sum = sum + (get(i, k) * matrix.get(k, j));
            }
            _copy.set(i, j, sum);
        }
    }
    return _copy;
}

const Matrix Matrix::operator~() const {
    Matrix _copy = *this;
    _copy.row = col;
    _copy.col = row;
    for (int i = 0; i < _copy.row; i++) {
        for (int j = 0; j < _copy.col; j++) {
            _copy.set(i, j, get(j, i));
        }
    }
    return _copy;
}

ostream& operator<<(ostream & out, const Matrix & matrix) {
    for (int i = 0; i < matrix.row; i++) {
        for (int j = 0; j < matrix.col; j++){
            out << matrix.get(i, j);
            out << " ";
        }
        out << '\n';
    }
    return out;
}

Matrix& Matrix::operator=(const Matrix &matrix) {
    for (int i = 0; i < col * row; i++)
        item[i] = matrix.item[i];
    return *this;
}

Matrix::~Matrix() {
    delete []item;
}

const Matrix operator*(int a, const Matrix &matrix){
    Matrix _copy = matrix;
    for (int i = 0; i < _copy.col * _copy.row; i++) {
        _copy.item[i] = _copy.item[i] * a;
    }
    return _copy;
}