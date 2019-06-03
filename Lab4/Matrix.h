//
// Created by asus on 2019/5/31.
//

#ifndef LAB4_MATRIX_H
#define LAB4_MATRIX_H
#include <cassert>
#include "Bignum.h"
class Matrix{
private:
    BigNum *item = nullptr;
    int row,col;
public:
    static int count;
//    Matrix();
    Matrix(int n);
    Matrix(int row, int col);
    Matrix(const Matrix& matrix);
    void set(int i, int j, const BigNum & bigNum)const ;
    const BigNum get(int i, int j)const ;
    const Matrix operator+(const Matrix& matrix) const ;
    const Matrix operator-(const Matrix& matrix) const ;
    const Matrix operator*(const Matrix& matrix) const ;
    const Matrix operator*(const int& mul) const ;
    Matrix& operator+=(const Matrix& matrix);
    Matrix& operator-=(const Matrix& matrix);
    Matrix& operator=(const Matrix& matrix);
    friend const Matrix operator*(int a,const Matrix& matrix);
    friend ostream& operator<<(ostream&,  const Matrix&);   //重载输出运算符
    const Matrix operator~() const;
    ~Matrix();
};
#endif //LAB4_MATRIX_H
