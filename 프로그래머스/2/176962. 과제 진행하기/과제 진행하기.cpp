#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>

using namespace std;

stack<pair<string, int>> st;



int time_to_timer(string time) {
    int hour = stoi(time.substr(0, 2));
    int minute = stoi(time.substr(3, 2));

    return (hour * 60 + minute);
}

bool compare(vector<string> a, vector<string> b) {
    return (time_to_timer(a[1]) <= time_to_timer(b[1]));
}

vector<string> solution(vector<vector<string>> plans) {
    sort(plans.begin(), plans.end(), compare);
    plans.push_back({"NULL", "26:00", "0"});

    vector<string> answer;

    int current = time_to_timer(plans.front()[1]);
    for(int i=0; i<plans.size()-1; i++) {
        int start = time_to_timer(plans[i][1]);
        int next = time_to_timer(plans[i+1][1]);
        int playtime = stoi(plans[i][2]);

        if(current < start) {
            while(!st.empty() && current < start) {
                if(current + st.top().second <= start) {
                    answer.push_back(st.top().first);
                    current += st.top().second;
                    st.pop();
                }
                else {
                    st.top().second -= (start - current);
                    current = start;
                }
            }       
        }

        if(start + playtime <= next) {
            answer.push_back(plans[i][0]);
            current += playtime;
        }
        else {
            playtime -= (next - start);
            current = next;
            st.push(make_pair(plans[i][0], playtime));
        }
    }

    while(!st.empty()) {
        answer.push_back(st.top().first);
        st.pop();
    }

    return answer;
}