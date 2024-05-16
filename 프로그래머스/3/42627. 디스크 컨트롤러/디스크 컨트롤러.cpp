#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

typedef pair<int, int> pii;

struct compare {
    bool operator()(pii prev, pii next) {
        return prev.second > next.second;
    }  
};
priority_queue<pii, vector<pii>, compare> pq;

int solution(vector<vector<int>> jobs) {

    
    sort(jobs.begin(), jobs.end());

    int current = 0, average = 0, idx = 0;
    while(idx < jobs.size()) {
        if(jobs[idx][0] <= current) {
            pq.push({jobs[idx][0], jobs[idx][1]});
            idx++;
        }
        else {
            if(!pq.empty()) {
                average += current - pq.top().first + pq.top().second;
                current += pq.top().second;
                pq.pop();
            }
            else
                current = jobs[idx][0];
        }
    }

    while(!pq.empty()) {
        average += current - pq.top().first + pq.top().second;
        current += pq.top().second;

        pq.pop();
    }

    return (int)(average / jobs.size());
}