#include <iostream>
#include <vector>
#include <set>

using namespace std;

int n, w, s, e;
vector<int> weight;
vector<vector<long long>> dp;
vector<vector<int>> adj;
set<int> vertex;

void build_tree_dp_table(int current, int parent) {
    for(auto next: adj[current]) {
        if(next != parent) {
            build_tree_dp_table(next, current);
            
            dp[current][0] += max(dp[next][0], dp[next][1]);
            dp[current][1] += dp[next][0];
        }
    }
}

void trace_independent_node(int current, int parent, int is_independent) {
    
    if(is_independent)
        vertex.insert(current);
        

    for(auto next: adj[current]) {
        if(next != parent) {
            if(is_independent) trace_independent_node(next, current, is_independent ^ 1);
            else {
                if(dp[next][0] > dp[next][1]) trace_independent_node(next, current, 0);
                else trace_independent_node(next, current, 1);
            }
        }
    }
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);    

    cin >> n;
    weight.resize(n + 1);
    adj.resize(n + 1);
    for(int node=1; node<=n; node++) cin >> weight[node];
    for(int i=1; i<n; i++) {
        cin >> s >> e;
        adj[s].push_back(e), adj[e].push_back(s);
    }
    
    dp.resize(n + 1, vector<long long>(2, 0ll));
    for(int node=1; node<=n; node++) dp[node][1] = weight[node];
    build_tree_dp_table(1, 0);

    cout << max(dp[1][0], dp[1][1]) << "\n";
    if(dp[1][0] > dp[1][1]) trace_independent_node(1, 0, 0);
    else trace_independent_node(1, 0, 1);

    for(auto iter=vertex.begin(); iter != vertex.end(); iter++) {
        cout << *iter << " ";
    }
}