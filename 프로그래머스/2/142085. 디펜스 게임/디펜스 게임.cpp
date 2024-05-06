#include <string>
#include <vector>
#include <queue>
#include <functional>
#include <iostream>

using namespace std;

priority_queue<int, vector<int>, greater<int>> pq;

int solution(int n, int k, vector<int> enemy) {
    int answer = 0;
    for(auto e: enemy) {
        pq.push(e);
        if(pq.size() > k) {
            n -= pq.top();
            pq.pop();
        }

        if(n < 0)
            return answer;
        answer++;
    }
    
    return enemy.size();
}