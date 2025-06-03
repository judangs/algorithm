#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>


using namespace std;
typedef pair<int, int> pii;

int n, h, o, d;
vector<pair<int, int>> position;

struct compare {
    bool operator()(const pii & l, const pii & r) {
        if(l.first == r.first)
            return l.second > r.second;
        return l.first > r.first;
    }
};

priority_queue<pii, vector<pii>, compare> pq;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    
    cin >> n;
    for(int i=0; i<n; i++) {
        cin >> h >> o;
        if(h > o) swap(h, o);
        position.push_back({h, o});
    }

    cin >> d;

    sort(position.begin(), position.end(), [](pair<int, int> a, pair<int, int> b) {
        if(a.second == b.second)
            return a.first < b.first;
        return a.second < b.second;
    });

    int ptr = 0, end, start;
    int answer = 0;
    while(ptr < n) {
        end = position[ptr].second, start = end - d;
        pq.push(position[ptr++]);
        while(!pq.empty() && pq.top().first < start) 
            pq.pop();

        answer = max(answer, (int) pq.size());
    }

    cout << answer;
}