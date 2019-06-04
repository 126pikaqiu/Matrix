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
class RPN{
private:
    string s;
public:
    int precedence(char op) const ;
    RPN(const string & s1);
    vector<string> toRPN();
    string scan(const string & s1);
};
#endif //LAB4_RPN_H
