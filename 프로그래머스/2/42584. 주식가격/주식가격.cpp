#include <string>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

stack<pair<int, int>> st;

vector<int> solution(vector<int> prices) {
    
    int end = prices.size() - 1;
    vector<int> answer(end + 1, 0);
    
    st.push(make_pair(end, 0));
    
    int current_time = 0;
    for(int i=0; i<end; i++) {
        if(st.top().second <= prices[i]) {
            st.push(make_pair(i, prices[i]));
        }
        else {
            while(st.top().second > prices[i]) {
                int idx = st.top().first;
                int price = st.top().second;
                
                st.pop();
                //cout << "idx: " << idx << " value: " << current_time - idx << endl;
                answer[idx] = current_time - idx;
            }
            
            st.push(make_pair(i, prices[i]));
        }
        current_time++;
    }
    
    while(!st.empty()) {
        int idx = st.top().first;
        int price = st.top().second;
        
        st.pop();
        
        answer[idx] = current_time - idx;
    }    
    return answer;
}