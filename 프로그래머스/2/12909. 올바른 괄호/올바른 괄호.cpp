#include <string>
#include <iostream>
#include <stack>

using namespace std;

stack<int> st;

bool solution(string s) {
    for(int i=0; i<s.size(); i++) {
        if(s[i] == '(') {
            st.push(i);
        }
        else {
            if(st.empty())
                return false;
            st.pop();
        }
    }

    if(st.empty())
        return true;
    else
        return false;
}