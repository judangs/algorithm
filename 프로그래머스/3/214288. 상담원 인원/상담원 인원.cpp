#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

vector<int> prev_wait;

int solve(vector<vector<int>> & reqs, int k, int mentor) {
    priority_queue<int, vector<int>, greater<int>> pq(mentor, 0);
    int wait_time = 0;
    for(int i=0; i<reqs.size(); i++) {
        if(reqs[i][2] - 1 == k) {
            int start = reqs[i][0];
            int time = reqs[i][1];

            int mentor_finish = pq.top();
            pq.pop();

            if(start >= mentor_finish) {
                pq.push(start + time);
            }
            else {
                wait_time += mentor_finish - start;
                pq.push(mentor_finish + time);
            }
        }
    }
    
    return wait_time;
}

int solution(int k, int n, vector<vector<int>> reqs) {
    
    vector<int> mentor(k, 1);
    prev_wait.resize(k, 0);

    for(int i=0; i<k; i++) {
        prev_wait[i] = solve(reqs, i, mentor[i]);
    }



    while(n - k> 0) {
        vector<int> wait_time(k, 0);

        for(int i=0; i<k; i++) {
            wait_time[i] = prev_wait[i] - solve(reqs, i, mentor[i] + 1);
        }

        int idx = max_element(wait_time.begin(), wait_time.end()) - wait_time.begin();
        mentor[idx]++;

        prev_wait[idx] = prev_wait[idx] - wait_time[idx];
        n--;
    }

    int answer = 0;
    for(int i=0; i<k; i++) {
        answer += solve(reqs, i, mentor[i]);
    }
    
    return answer;
}