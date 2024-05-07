#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

struct compare {
    bool operator()(pair<int, int> a, pair<int, int> b) {
        return a.second < b.second;
    }
};

priority_queue<pair<int, int>, vector<pair<int, int>>, compare> pq;

int solution(vector<int> stones, int k) {
    for(int i=0; i<k; i++) {
        pq.push(make_pair(i, stones[i]));
    }

    int answer = pq.top().second;
    int end = k;
    while(end < stones.size()) {
        pq.push(make_pair(end, stones[end]));
        while(pq.top().first < (end - k + 1)) {
            pq.pop();
        }
        end++;
        answer = min(answer, pq.top().second);
    }

    return answer;
}