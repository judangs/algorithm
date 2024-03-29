#include <string>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

long long solution(int n, vector<int> works) {
    long long answer = 0;
    
    priority_queue<int> pq(works.begin(), works.end());
    
    for(int i=0; i<n; i++) {
        int current = pq.top();
        if(current > 0) {
            pq.pop();
            pq.push(current - 1);
        }
    }
    
    while(!pq.empty()) {
        answer += pow(pq.top(), 2);
        pq.pop();
    }
    return answer;
}