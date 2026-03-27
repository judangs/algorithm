#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<vector<pair<int, int>>> tree;
const int inf = 1e9;
struct Node {
    int now;
    int cost;
    
    bool operator>(const Node & o) const {
        return cost > o.cost;
    }
};

vector<bool> bfs(int type, int n, vector<bool> & visit) {
    
    vector<bool> ret = visit;
    vector<int> distance(n + 1, inf);
    
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    for(int i = 1; i <= n; i++)
        if(ret[i]) {
            distance[i] = 0;
            pq.push({ i, 0 });
        }
    
    while(!pq.empty()) {
        
        auto node = pq.top(); pq.pop();
        
        if(node.cost > distance[node.now]) continue;
        for(auto & [next, t]: tree[node.now]) {
            if(!ret[next] && t == type && node.cost + 1 < distance[next]) {
                ret[next] = true;
                distance[next] = node.cost + 1;
                pq.push({ next, distance[next] });
            }
        }
    }
    
    return ret;
}

int dfs(int depth, int k, int n, vector<bool> & visit) {
    
    if(depth == k) {
        int count = 0;
        for(int i = 1; i <= n; i++)
            if(visit[i]) count++;
        return count;
    }
    
    int ret = 0;
    
    for(int type = 1; type <= 3; type++) {
        vector<bool> next = bfs(type, n, visit);
        ret = max(ret, dfs(depth + 1, k, n, next));
    }
    
    return ret;
}

int solution(int n, int infection, vector<vector<int>> edges, int k) {
    
    tree = vector<vector<pair<int, int>>> (n + 1);
    for(auto & edge: edges) {
        int s = edge[0], e = edge[1], type = edge[2];
        tree[s].push_back({ e, type });
        tree[e].push_back({ s, type });
    }
    
    vector<bool> visit(n + 1, false); visit[infection] = true;
    int ans = dfs(0, k, n, visit);
    return ans;
}
