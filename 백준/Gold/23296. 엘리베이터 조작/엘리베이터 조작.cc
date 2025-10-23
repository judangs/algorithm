#include <iostream>
#include <vector>
#include <algorithm>

#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int N;
vector<vector<int>> adj(100001);
int indegree[100001] = {0, };
bool visited[100001] = {false, };

vector<int> clicks;

void dfs(int now) {
    for(auto & next: adj[now]) {
        clicks.push_back(next);
        if(visited[next]) continue;
        visited[next] = true;
        dfs(next);
    }
}

int main() {

    fastio;
    cin >> N;
    for(int floor = 1; floor <= N; floor++) {
        int next; cin >> next;
        adj[floor].push_back(next);
        indegree[next]++;
    }
    
    for(int node = 1; node <= N; node++) {
        if(visited[node]) continue;
        if(indegree[node] == 0) {
            clicks.push_back(node);
            visited[node] = true;
            dfs(node);
        }
    }

    for(int node = 1; node <= N; node++) {
        if(visited[node]) continue;
        clicks.push_back(node);
        visited[node] = true;
        dfs(node);
    }

    if(clicks.front() == 1)  clicks.erase(clicks.begin());
    
    cout << clicks.size() << '\n';
    for(auto & click: clicks) cout << click << ' ';
    cout << '\n';
}