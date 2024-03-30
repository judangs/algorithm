#include <string>
#include <vector>
#include <queue>
#include <functional>
#include <iostream>

using namespace std;

int solution(vector<int> scoville, int K) {
    priority_queue<int, vector<int>, greater<int>> pq;
    
    for(int scov: scoville) {
        pq.push(scov);
    }
    
    int answer = 0;
    while(pq.top() < K) {
        int first = pq.top();
        pq.pop();
        
        if(pq.empty()) return -1;
        int second = pq.top();
        pq.pop();
        
        pq.push(first + (second * 2));
        answer++;
    }
    
    return answer;
}