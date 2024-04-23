#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <iostream>

using namespace std;

bool compare(vector<int> a, vector<int> b) {
    return a[0] < b[0];
}

int solution(vector<vector<int>> routes) {
    sort(routes.begin(), routes.end(), compare);

    stack<pair<int, int>> st;
    st.push(make_pair(routes.front()[0], routes.front()[1]));
    
    for(int i=1; i<routes.size(); i++) {
        if(st.top().second < routes[i][0]) {
            st.push(make_pair(routes[i][0], routes[i][1]));
        }
        else {
            st.top().first = routes[i][0];
            st.top().second = min(st.top().second, routes[i][1]);
        }
    }

    int answer = st.size();
    return answer;
}