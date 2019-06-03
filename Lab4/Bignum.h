//
// Created by asus on 2019/5/31.
//

#ifndef LAB4_BIGNUM_H
#define LAB4_BIGNUM_H

#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
using namespace std;

#define MAXLEN 40
#define MAXN 99   //每一个char储存位最大存入99
#define MAXSIZE 10
#define DLEN 2
class BigNum
{
private:
    char cache[MAXLEN];    //可以控制大数的位数
    int len;       //大数长度
public:
    static int count;
    BigNum();   //构造函数
    BigNum(const int a);       //将一个int类型的变量转化为大数
    BigNum(const char* s);     //将一个字符串类型的变量转化为大数
    BigNum(const BigNum &);  //拷贝构造函数
    const BigNum operator+(const BigNum &) const;   //重载加法运算符，两个大数之间的相加运算
    const BigNum operator-(const BigNum &) const;   //重载减法运算符，两个大数之间的相减运算
    const BigNum operator*(const BigNum &) const;   //重载乘法运算符，两个大数之间的相乘运算
    bool operator > (const BigNum &) const;    //重载除法运算符，大数对一个整数进行相除运算
    friend ostream& operator<<(ostream&,  const BigNum&);   //重载输出运算符
};
#endif //LAB4_BIGNUM_H
