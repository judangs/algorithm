#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <cmath>
#include <algorithm>

using namespace std;

int N;

long long compress(vector<int> & stones, vector<char> & color) {
    vector<int> trace;
    
    int top = 0, current = stones.front();
    for(int now = 1; now < N; now++) {
        if(color[now] == color[now - 1]) {
            if(current < stones[now]) {
                current = stones[now]; 
                top = now;
            }
        }
        else {
            trace.push_back(top);
            current = stones[now]; 
            top = now;
        }
    }
    
    trace.push_back(top);

    priority_queue<int, vector<int>, less<int>> pq;
    for(int now = 0; now < trace.size(); now++) {
        if(now == 0 || now == trace.size() - 1) continue;
        pq.push(stones[trace[now]]);
    }

    long long ret = 0;
    for(int count = ceil((double) pq.size() / 2.0); 0 < count; count--) {
        ret += pq.top(); 
        pq.pop();
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;
    vector<int> stones(N); 
    vector<char> color(N);
    for(auto & c: color) cin >> c;
    for(auto & stone: stones) cin >> stone;

    if(N <= 2) cout << "0" << endl;
    else if(N == 3) {
        if(color[0] != color[1] && color[1] != color[2])
            cout << stones[1] << endl;
        else
            cout << "0" << endl;
    }
    else {
        long long answer = compress(stones, color);
        cout << answer << endl;
    }
}