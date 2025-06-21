#include <iostream>
#include <cstring>
#include <stack>
#include <stdlib.h>

using namespace std;

string pattern;
stack<char> st;


void invalid() {
    cout << "0";
    exit(0);
}

int main() {
    
    cin >> pattern;
    
    if(pattern.front() != '(' && pattern.front() != '[') {
        invalid();
    }

    int answer = 0, tmp = (pattern.front() == '(') ? 2 : 3;
    st.push(pattern.front());

    for(int idx=1; idx<pattern.size(); idx++) {
        auto & prev = pattern[idx - 1], & current = pattern[idx];
        if(current == '(') {
            tmp *= 2; st.push(current);
        }
        if(current == '[') {
            tmp *= 3; st.push(current);
        }
        if(current == ')') {
            if(st.empty() || st.top() != '(') invalid();
            if(prev == '(') answer += tmp;
            tmp /= 2;

            st.pop();
        }
        if(current == ']') {
            if(st.empty() || st.top() != '[') invalid();
            if(prev == '[') answer += tmp;
            tmp /= 3;

            st.pop();
        }
    }

    if(st.empty()) cout << answer;
    else invalid();    
}