//
// Created by asus on 2019/6/3.
//

#ifndef LAB4_RPN_H
#define LAB4_RPN_H
#include <iostream>
#include <stack>
#include <vector>
#include<cstring>
#include<cstdlib>
#include<cstdio>
using namespace std;
#define EQUAL_HANDLE
class RPN{
private:
    string s;
    string scan(const string & s1);
    bool equal_handle(char ne, char ol);
    int precedence(char op) const ;
public:
    RPN(const string & s1);
    vector<string> toRPN();
};
#endif //LAB4_RPN_H
