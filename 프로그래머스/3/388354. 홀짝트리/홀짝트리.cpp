#include <string>
#include <vector>
#include <map>

using namespace std;

vector<vector<int>> tree;
vector<pair<int, int>> forest;

int idx = 0;
map<int, int> toidx;

void dfs(int now, int parent, int idx, vector<bool> & visit, vector<int> & nodes) {
    
    visit[now] = true;
    if(nodes[now] % 2 == tree[now].size() % 2) forest[idx].first++;
    if(nodes[now] % 2 != tree[now].size() % 2) forest[idx].second++;        
    
    
    for(auto child: tree[now]) {
        if(child != parent) {
            dfs(child, now, idx, visit, nodes);
        }
    }
    
}

vector<int> solution(vector<int> nodes, vector<vector<int>> edges) {
    
    int n = nodes.size();
    tree = vector<vector<int>> (n);
    
    for(auto node: nodes)
        toidx[node] = idx++;
    
    for(auto edge: edges) {
        int s = toidx[edge.front()], e = toidx[edge.back()];
        tree[s].push_back(e);
        tree[e].push_back(s);
    }
    
    vector<bool> visit(n, false);
    for(int i = 0; i < n; i++) {
        if(!visit[i]) {
            forest.push_back({ 0, 0 });
            dfs(i, -1, forest.size() - 1, visit, nodes);
        }
    }
    
    vector<int> ans = { 0, 0 };
    for(auto & [f, r]: forest) {
        if(f == 1) ans[0]++;
        if(r == 1) ans[1]++;
    }
    
    return ans;
    
}