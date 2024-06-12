#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>

using namespace std;

stack<char> st;

int remove_pattern(string & s) {
    int count = 0;
    for(int i=0; i<s.size(); i++) {
        st.push(s[i]);
        if(st.size() >= 3) {
            int first = st.top();
            if(first != '0') continue;
            
            st.pop();
            int second = st.top();
            if(second != '1') {
                st.push(first);
                continue;
            }

            st.pop();
            int third = st.top();
            if(third != '1') {
                st.push(second);
                st.push(first);
                continue;
            }

            st.pop();

            count++;
        }
    }

    return count;
}

int find_insert_pos(string remain) {
    for(int i=remain.size()-1; i>=0; i--) {
        if(remain[i] == '0') return i + 1;
    }
    return 0;
}

vector<string> solution(vector<string> s) {
    
    vector<string> answer;
    for(string current: s) {
        int count = remove_pattern(current);

        string remain = "";
        while(!st.empty()) {
            remain += st.top();
            st.pop();
        }

        reverse(remain.begin(), remain.end());
        
        while(count != 0) {
            int pos = find_insert_pos(remain); 
            remain.insert(pos, "110");
            count--;
        }

        answer.push_back(remain);
    }

    return answer;
}