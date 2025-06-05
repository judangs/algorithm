#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

#define INF 1e9

using namespace std;

int N, M, K, R, A, B, D;
vector<int> problem;
vector<vector<pair<int ,int>>> adj;

struct Node {
    int idx;
    int algo;

    bool operator>(const Node & o) const {
        return algo > o.algo;
    }
};

priority_queue<Node, vector<Node>, greater<Node>> pq;

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;

    problem.resize(N + 1);
    adj.resize(N + 1);

    for(int idx=1; idx<=N; idx++) {
        cin >> problem[idx];
        pq.push({idx, problem[idx]});
    }

    cin >> K;
    for(int i=0; i<K; i++) {
        cin >> A >> B >> D;
        adj[A].push_back({B, D});
    }

    vector<bool> visit(N + 1, false);

    int answer = 0, solved = 0;
    while(!pq.empty() && solved != M) {
        auto node = pq.top();
        pq.pop();

        answer = max(answer, node.algo);
        if(!visit[node.idx]) {
            visit[node.idx] = true;
            solved++;

            for(auto next: adj[node.idx]) {
                if(!visit[next.first]) {
                    problem[next.first] -= next.second;
                    pq.push({next.first, problem[next.first]});    
                }
            }                
        }
    }

    cout << answer;

}