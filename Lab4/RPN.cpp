//
// Created by asus on 2019/6/3.
//

#include "RPN.h"
RPN::RPN(const string &s1) {
    s = s1;
    while (s.find("+=") != string::npos) {
        s.replace(s.find("+="), 2, ">");
    }
    while (s.find("-=") != string::npos) {
        s.replace(s.find("-="), 2, "<");
    }
    if (s.at(0) == '-') {
        s = string("mzero") + s;
    }
    s = scan(s);
}

string RPN::scan(const string &s) {
    bool flag = false;
    string s1(s);
    int j = s.length();
    for (int i = 0; i < j; i++) {
        if(precedence(s1.at(i)) > 0) {
            if (flag) {
                s1.insert(i, string("mzero"), 0, 5);
                i += 5;
                j += 5;
            } else {
                flag = true;
            }
        } else {
            flag = false;
        }
    }
    return s1;
}
int RPN::precedence(char op) const {
    switch(op){
        case '=':
            return 1;
        case '<':
        case '>':
            return 2;
        case '+':
        case '-':
            return 3; //定义加减运算的优先级为1
        case '*':
            return 4; //定义乘除运算的优先级为2
        case '~':
            return 5;
        case '\0':
        default:
            return 0; //定义在栈中的左括号和栈底字符的优先级为0
    }
}
vector<string> RPN::toRPN() {
    vector<string> rpn;
    stack<char> sta;
    sta.push('\0');//栈底字符
    int i = 0;
    char ch;
    while(i < s.length()) {
        ch = s.at(i);
        if(ch == ' '){}
        else if(precedence(ch) > 0){
            char w = sta.top();
            while(precedence(w) >= precedence(ch)) {
                char value[2] = {w, 0};
                string item(value);
                rpn.push_back(item);  //栈里的大的话 栈那个写入
                sta.pop(); //继续出栈   这是一个循环
                w = sta.top();
            }
            sta.push(ch);  //压入此字符
        }
        else{
            char item[10];
            int j = 0;
            while((ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z')){
                item[j++] = ch;   //写入输出字符串（后缀式）
                i++;
                if (i == s.length()){
                    break;
                }
                ch = s.at(i);
            }
            i--;
            item[j] = '\0';
            string r(item);
            rpn.push_back(r);
        }
        i++;
    }
    ch = sta.top();
    sta.pop();
    while(ch != '\0'){
        char value[2] = {ch, 0};
        string item(value);
        rpn.push_back(item);    //写入
        ch = sta.top();
        sta.pop();
    }
    return rpn;
}