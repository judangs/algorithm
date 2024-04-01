#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <iostream>

using namespace std;

int solution(vector<int> order) {
    int answer = 0;
    
    stack<int> st;
    queue<int> q;
    
    for(int i: order) 
        q.push(i);
    
    for(int i=1; i<=order.size(); i++) {
        if(!st.empty()) {
            if(q.front() == st.top()) {
                while(!q.empty() && !st.empty()) {
                    if(q.front() == st.top()) {
                        answer++;
                        q.pop();
                        st.pop();                        
                    }
                    else {
                        break;
                    }
                }
            }
        }
        if(q.front() == i) {
            answer++;
            q.pop();
        }
        else {
            st.push(i);            
        }

    }
    
    while(!q.empty() && !st.empty()) {
        if(q.front() == st.top()) {
            answer++;
            q.pop();
            st.pop();            
        }
        else {
            break;
        }

    }
    return answer;
}