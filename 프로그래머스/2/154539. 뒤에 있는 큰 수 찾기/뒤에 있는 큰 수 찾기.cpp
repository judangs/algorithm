#include <string>
#include <vector>
#include <stack>

using namespace std;

stack<pair<int, int>> st;


vector<int> solution(vector<int> numbers) {
    
    vector<int> answer(numbers.size(), -1);
    
    for(int i=0; i<numbers.size(); i++) {
        while(!st.empty() && st.top().second < numbers[i]) {
            answer[st.top().first] = numbers[i];
            st.pop();
        }
        
        st.push(make_pair(i, numbers[i]));
    }
    
    return answer;
}