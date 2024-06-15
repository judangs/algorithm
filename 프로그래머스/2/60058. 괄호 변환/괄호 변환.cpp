#include <string>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

bool check_valid(string param) {
    stack<char> st;
    for(int i=0; i<param.size(); i++) {
        if(param[i] == '(') {
            st.push(param[i]);
        }   
        else {
            if(st.empty()) return false;
            st.pop();
        }
    }

    return true;
}

string divide(string current) {

    if(current.empty()) return "";
    
    int open = 0, close = 0, idx;
    for(idx=0; idx<current.size(); idx++) {
        if(current[idx] == '(') open++;
        else close++;

        if(open == close) break;
    }

    string u = current.substr(0, idx + 1);
    string v = current.substr(idx + 1);

    if(check_valid(u) == true) {
        v = divide(v);
        return (u + v);
    }
    else {
        string next = '(' + divide(v) + ')';
        for(int i=1; i<u.size()-1; i++) {
            if(u[i] == '(') next += ')';
            else next += '(';
        }

        return next;
    }
}

string solution(string p) {    
    return divide(p);
}