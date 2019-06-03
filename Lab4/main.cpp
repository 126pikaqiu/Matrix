#include <iostream>
#include "Matrix.h"
#include "Bignum.h"
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
        cout <<"The file matrix.in not found.";
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

vector<Matrix> compute(const map<string, Matrix> & map){
    vector<Matrix> v;
    regex priority[] = {regex("~"),regex("*"),regex("+|-"),regex("+=|-=")};
    return v;
}

void output(const vector<Matrix> & v) {
    ofstream mafile;
    mafile.open("./res/result.out", ios::out);
    if (mafile.fail()) {
        cout <<"The file result.out not found.";
        return;
    }
    for (const auto& val : v){
        cout << val << endl;
    }
    mafile.close();
}
int main(int argv, char *arg[]) {
    map<string, Matrix> matMap;
    matMap = getMatrix();
    Matrix m = matMap.find("A")->second + matMap.find("B")->second;
//    cout << m << endl;
//    cout << ~matMap.find("B")->second;
//    output(compute(matMap));
    return 0;
}



