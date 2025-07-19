#include <iostream>
#include <vector>
#include <queue>

#define INF 1e9

using namespace std;

int N, M, k;
vector<vector<int>> adj;
vector<int> cost;

int bfs(int start, vector<bool> & visit) {
    queue<int> q;
    q.push(start);
    visit[start] = true;
    
    int ret = INF;
    while(!q.empty()) {
        int now = q.front(); q.pop();

        ret = min(ret, cost[now]);
        
        for(auto next: adj[now]) {
            if(!visit[next]) {
                visit[next] = true;
                q.push(next);
            }
        }
    }

    return ret;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> M >> k;
    cost.resize(N + 1, 0);
    adj.resize(N + 1);

    for(int i=1; i<=N; i++) cin >> cost[i];

    for(int i=0; i<M; i++) {
        int v, w; cin >> v >> w;
        adj[v].push_back(w); adj[w].push_back(v);
    }

    vector<bool> visit(N + 1, false);
    
    int answer = 0;
    for(int i=1; i<=N; i++) {
        if(!visit[i]) answer += bfs(i, visit);
    }

    if(answer > k) cout << "Oh no" << endl;
    else 
        cout << answer << endl;
    

}