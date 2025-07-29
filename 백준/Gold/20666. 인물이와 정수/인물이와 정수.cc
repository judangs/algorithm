#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

#define MAXMONSTER 100001

using namespace std;
typedef long long ll;

int N, M, p;
ll monster[MAXMONSTER];

vector<pair<int, int>> item[MAXMONSTER];

struct Node {
    int idx;
    ll level;
    
    bool operator>(const Node & o) const {
        return level > o.level;
    }
};
priority_queue<Node, vector<Node>, greater<Node>> pq;


int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;
    for(int i=1; i<=N; i++) cin >> monster[i];
    
    cin >> p;
    for(int i=0; i<p; i++) {
        int a, b, t; cin >> a >> b >> t;

        monster[b] += t;
        item[a].push_back({b, t});
    }

    for(int i=1; i<=N; i++)
        pq.push({i, monster[i]});

    vector<bool> visit(N, false);

    int hunt = 0; ll answer = 0;
    while(!pq.empty() && hunt < M) {
        auto node = pq.top();
        pq.pop();

        if(visit[node.idx]) continue;
        visit[node.idx] = true;
        
        hunt++;
        answer = max(answer, node.level);
        
        for(auto next: item[node.idx]) {
            if(visit[next.first]) continue;
            monster[next.first] -= next.second;
            pq.push({next.first, monster[next.first]});
        }
    }

    cout << answer << endl;
    

}