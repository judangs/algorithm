#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdio>

using namespace std;

int T, N, K;

bool compare(pair<int, int> a, pair<int, int> b) {
    return a.second > b.second;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;

    for(int k=1; k<=T; k++) {
        cin >> N >> K;

        vector<pair<int, int>> person(N, {0, 0});
        vector<bool> visit(K, false);
        int want, cost;
        for(int i=0; i<N; i++) {
            cin >> want;
            person[i].first = want;
        }
        for(int i=0; i<N; i++) {
            cin >> cost;
            person[i].second = cost;
        }

        priority_queue<int, vector<int>, greater<int>> pq;
        sort(person.begin(), person.end(), compare);
        int count = 0;
        for(auto p: person) {
            if(visit[p.first] == false) {
                visit[p.first] = true;
                count++;
            }
            else {
                pq.push(p.second);
            }
        }
        unsigned long long result = 0;
        while(count < K) {
            result += pq.top();
            pq.pop();
            count++;
        }

        cout << "#" << k << " " << result << "\n";
        
    }
}
