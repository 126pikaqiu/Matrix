#include <iostream>
#include "Matrix.h"
#include "Bignum.h"
#include "RPN.h"
#include <map>
#include <fstream>
#include<utility>
#include <regex>
using namespace std;

map<string,Matrix> getMatrix() {
    map<string, Matrix> matMap;
    ifstream mafile;
    mafile.open("./res/matrix.in", ios::in);
    if (mafile.fail()) {
        cout << "The file matrix.in not found." <<endl;
        assert(0);
        return matMap;
    }
    string line;
    getline(mafile,line);
    while (getline(mafile,line)){
        string name = line.substr(line.find_first_not_of(' '), line.find(' ') - line.find_first_not_of(' '));
        Matrix matrix(3);
        for (int i = 0; i < 3; i++) {
            getline(mafile,line);
            int start = line.find_first_not_of(' ');
            int end;
            for (int j = 0; j < 3; j++){
                end = line.find(' ', start);
                if (end == string::npos){
                    end = line.length();
                }
                char value[end - start];
                for (int k = 0; k < end - start; k++) {
                    value[k] = line.at(start + k);
                }
                value[end - start] = '\0';
                matrix.set(i, j, BigNum(value));
                start = end + 1;
            }

        }
        matMap.insert(pair<string,Matrix>(name,matrix));
    }
    mafile.close();
    return matMap;
}

int op(char op){
    switch(op){
        case '<':
        case '>':
        case '+':
        case '-':
        case '*':
        case '~':
        case '=':
            return 1;
        default:
            return 0; 
    }
}

bool isNum(const string& str){
    for (char i : str) {
        if (i < '0' || i > '9'){
            return false;
        }
    }
    return true;
}

vector<Matrix> compute(map<string, Matrix> & matMap){
    vector<Matrix> v;
    ifstream mafile;
    mafile.open("./res/expression.in", ios::in);
    if (mafile.fail()) {
        cout<< "The file expression.in not found." << endl;
        assert(0);
        return v;
    }
    string line;
    while (getline(mafile, line)){
        RPN rpn(line);
        vector<string> rp = rpn.toRPN();
        stack<string> help;
        Matrix result(3);
        for (auto & i : rp) {
            if (!op(i.at(0))) {
                help.push(i);
                if (!isNum(help.top())) {
                    result = matMap.find(help.top())->second;
                }
            } else {
                string right,left;
                right = help.top();help.pop();
                switch (i.at(0)){
                    case '=':
                        left = help.top();help.pop();
                        result = matMap.find(right)->second;
                        help.push(left);
                        matMap.insert(pair<string, Matrix>(left, result));
                        break;
                    case '+':
                        left = help.top();help.pop();
                        result = matMap.find(left)->second + matMap.find(right)->second;
                        left.append("+").append(right);
                        help.push(left);
                        matMap.insert(pair<string, Matrix>(left, result));
                        break;
                    case '-':
                        left = help.top();help.pop();
                        result = matMap.find(left)->second - matMap.find(right)->second;
                        left.append("-").append(right);
                        help.push(left);
                        matMap.insert(make_pair(left, result));
                        break;
                    case '*':
                        left = help.top();help.pop();
                        if (isNum(left)) {
                            result = atoi(left.c_str()) * matMap.find(right)->second;
                        } else {
                            result = matMap.find(left)->second * matMap.find(right)->second;
                        }
                        left.append("*").append(right);
                        help.push(left);
                        matMap.insert(pair<string, Matrix>(left, result));
                        break;
                    case '~':
                        result = ~matMap.find(right)->second;
                        right.append("~");
                        help.push(right);
                        matMap.insert(pair<string, Matrix>(right, result));
                        break;
                    case '>':
                        left = help.top();help.pop();
                        help.push(left);
                        result = matMap.find(left)->second + matMap.find(right)->second;
                        matMap.insert(pair<string, Matrix>(left, result));
                        break;
                    case '<':
                        left = help.top();help.pop();
                        help.push(left);
                        result = matMap.find(left)->second - matMap.find(right)->second;
                        matMap.insert(pair<string, Matrix>(left, result));
                        break;
                }
            }
        }
        v.push_back(result);
    }
    return v;
}




void output(const vector<Matrix> & v) {
    ofstream mafile;
    mafile.open("./res/result.out", ios::out);
    if (mafile.fail()) {
        cout << "The file result.out not found." << endl;
        assert(0);
        return;
    }
    for (const auto& val : v){
        mafile << val;
        cout << val;
    }
    mafile.close();
}

int main(int argv, char *arg[]) {
    map<string, Matrix> matMap;
    matMap = getMatrix();
    matMap.insert(make_pair("mzero",Matrix(3)));
    output(compute(matMap));
    return 0;
}



