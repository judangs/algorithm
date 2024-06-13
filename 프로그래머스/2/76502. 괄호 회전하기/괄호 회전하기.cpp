#include <string>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

string move_left(string s, int left, int n) {
    
    string new_s(n, '|');
    for(int i=0; i<n; i++) {
        new_s[(i + n - left) % n] = s[i];
    }

    return new_s;
}

bool check_valid(string current) {
    stack<char> st;
    for(int i=0; i<current.size(); i++) {
        if(current[i] == '{' || current[i] == '[' || current[i] == '(') st.push(current[i]);
        else {
            if(st.empty()) return false;
            if(current[i] == '}' && st.top() != '{') return false;
            if(current[i] == ']' && st.top() != '[') return false;
            if(current[i] == '(' && st.top() != ')') return false;
            st.pop();
        }
    }

    if(st.empty()) return true;
    return false;
}

int solution(string s) {

    int answer = 0;
    for(int left=0; left<s.size(); left++) {
        string next = move_left(s, left, s.size());
        if(check_valid(next) == true)
            answer++;
    }

    return answer;
}