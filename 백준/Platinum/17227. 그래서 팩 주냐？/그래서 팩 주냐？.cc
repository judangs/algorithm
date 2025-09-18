#include <iostream>
#include <vector>
#include <algorithm>

#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;

const int inf = 1e9;
int N, E;
vector<vector<int>> tree;
vector<vector<int>> dp;
vector<int> indegree;
vector<vector<bool>> visited;

void dfs(int now, int turn) {

    if(tree[now].empty()) return;
    if(visited[now][turn]) return;
    visited[now][turn] = true;

    for(auto child: tree[now]) dfs(child, turn ^ 1);
    
    if(turn) {
        for(auto child: tree[now]) {
            dp[now][turn] = min(dp[now][turn], dp[child][turn ^ 1]);
        }
    }
    else {

        sort(tree[now].begin(), tree[now].end(), [&](int a, int b) {
            return dp[a][turn ^ 1] < dp[b][turn ^ 1];
        });
        
        vector<int> nxt;
        int sz = tree[now].size();
        for(int i = 0; i < sz; i++) {
            if(dp[tree[now][i]][turn ^ 1] == inf) 
                nxt.push_back(inf);
            else
                nxt.push_back(dp[tree[now][i]][turn ^ 1] + (sz - i - 1));
        }
        
        dp[now][turn] = min(dp[now][turn], *min_element(nxt.begin(), nxt.end()));
    }
}

int main() {
    
    fastio;
    cin >> N >> E;

    tree = vector<vector<int>> (N + 1);
    dp = vector<vector<int>> (N + 1, vector<int>(2, inf));
    indegree = vector<int> (N + 1, 0);
    visited = vector<vector<bool>> (N + 1, vector<bool> (2, false));

    for(int i = 0; i < E; i++) {
        int u, v; cin >> u >> v;
        indegree[v]++;
        tree[u].push_back(v);
    }

    dp[N][0] = 0; dp[N][1] = inf;

    int answer = inf;
    for(int i = 1; i <= N; i++) {
        if(!indegree[i]) {
            dfs(i, 0);
            answer = min(answer, dp[i][0]);
        }
    }
    
    cout << (answer == inf ? -1 : answer) << endl;

}