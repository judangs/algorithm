#include <string>
#include <vector>
#include <queue>

using namespace std;

queue<int> q;
vector<vector<int>> adj;

bool solution(int n, vector<vector<int>> path, vector<vector<int>> order) {
    
    vector<vector<int>> graph(n);
    adj.resize(n);
    vector<int> indegree(n, 0);
    for(int idx=0; idx<path.size(); idx++) {
        int s = path[idx][0], e = path[idx][1];
        graph[s].push_back(e);
        graph[e].push_back(s);
    }
    
    vector<bool> visit(n, false);
    visit[0] = true;
    q.push(0);
    
    while(!q.empty()) {
        int cur = q.front(); q.pop();
        
        for(int next: graph[cur]) {
            if(visit[next] == false) {
                adj[cur].push_back(next);
                indegree[next]++;
                visit[next] = true;
                q.push(next);
            }
        }
    }
    
    for(int idx=0; idx<order.size(); idx++) {
        int prev = order[idx][0];
        int next = order[idx][1];
        
        adj[prev].push_back(next);
        indegree[next]++;
    }
    
    for(int node=0; node<n; node++) {
        if(indegree[node] == 0)
            q.push(node);
    }
    
    for(int step=0; step<n; step++) {
        if(q.empty()) return false;
        
        int cur = q.front();
        q.pop();
        
        for(int next: adj[cur]) {
            indegree[next]--;
            if(indegree[next] == 0) {
                q.push(next);
            }
        }
    }
    
    return true;
}