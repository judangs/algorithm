#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>

using namespace std;

priority_queue<int, vector<int>, less<int>> pq;

int solution(vector<int> A, vector<int> B) {
    sort(A.rbegin(), A.rend());
    
    for(int b: B) {
        pq.push(b);
    }
    
    int answer = 0;
    for(int a: A) {
        if(a < pq.top()) {
            answer++;
            pq.pop();
        }
    }
    
    return answer;
}