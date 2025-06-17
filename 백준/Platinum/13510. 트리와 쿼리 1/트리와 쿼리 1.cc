#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define MAXNODE 100001
#define MAXK 22

using namespace std;
typedef pair<int, int> pii;

int N, M;
int u, v, w;
int chid = 1, id = 1;
int in[MAXNODE], out[MAXNODE];
int node2idx[MAXNODE];
int weight[MAXNODE];
int depth[MAXNODE];
int cost[MAXNODE];
int head[MAXNODE];
int channel[MAXNODE];
int parent[22][MAXNODE];

vector<vector<pii>> adj;

struct Segtree {
    vector<int> arr;
    
    Segtree(int sz) {
        arr.resize(sz, 0);
    }

    void update(int node, int l, int r, int idx, int val) {
        if(idx < l || r < idx) return;
        if(l == r && l == idx) {
            arr[node] = val;
            return;
        }

        int m = (l + r) / 2;
        update(2 * node, l, m, idx, val);
        update(2 * node + 1, m + 1, r, idx, val);
        arr[node] = max(arr[2 * node], arr[2 * node + 1]);
    }

    int query(int node, int l, int r, int s, int e) {
        if(r < s || e < l) return 0;
        if(s <= l && r <= e) return arr[node];
        
        int m = (l + r) / 2;
        return max(query(2 * node, l, m, s, e), 
                    query(2 * node + 1, m + 1, r, s, e));
    }
};

void dfs_node_ordering(int node, int par, int lv) {
    depth[node] = lv;
    parent[0][node] = par;
    weight[node] = 1;

    for(int k = 1; k < MAXK; k++) {
        if(parent[k-1][node] != 0) {
            parent[k][node] = parent[k-1][parent[k-1][node]];
        }
    }
    
    for(auto child: adj[node]) {
        if(child.first != par) {
            cost[child.first] = child.second;
            dfs_node_ordering(child.first, node, lv + 1);
            weight[node] += weight[child.first];
        }
    }
}

void hld(int node, int par) {
    node2idx[node] = id++;

    vector<pii> children;
    for(auto next: adj[node]) {
        if(next.first != par) {
            children.push_back(next);
        }
    }

    sort(children.begin(), children.end(), [](const pii & l, const pii & r) {
        return weight[l.first] > weight[r.first];
    });

    if(!children.empty()) {
        auto heavy = children.front();
        channel[heavy.first] = channel[node];
        hld(heavy.first, node);
    }

    for(int i = 1; i < children.size(); i++) {
        channel[children[i].first] = ++chid;
        head[chid] = children[i].first;
        hld(children[i].first, node);
    }
}

int query_lca_node(int u, int v) {
    if(depth[u] > depth[v]) swap(u, v);
    
    int diff = depth[v] - depth[u];
    for(int k = MAXK - 1; k >= 0; k--) {
        if(diff & (1 << k)) v = parent[k][v];
    }

    if(u == v) return u;

    for(int k = MAXK - 1; k >= 0; k--) {
        if(parent[k][u] != parent[k][v]) {
            u = parent[k][u];
            v = parent[k][v];
        }
    }

    return parent[0][u];
}

int sub_query(Segtree * seg, int l, int r, int u, int v) {
    int ret = 0;
    while(channel[u] != channel[v]) {
        int ut = head[channel[u]], vt = head[channel[v]];
        if(depth[ut] > depth[vt]) {
            ret = max(ret, seg->query(1, l, r, node2idx[ut], node2idx[u]));
            u = parent[0][ut];   
        }
        else {
            ret = max(ret, seg->query(1, l, r, node2idx[vt], node2idx[v]));
            v = parent[0][vt];
        }
    }

    if(u != v) {
        if(depth[u] > depth[v]) swap(u, v);
        ret = max(ret, seg->query(1, l, r, node2idx[u] + 1, node2idx[v]));
    }

    return ret;
}

int query(Segtree * seg, int u, int v, int l, int r) {
    int lca = query_lca_node(u, v);
    return max(sub_query(seg, l, r, u, lca), sub_query(seg, l, r, v, lca));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;
    adj.resize(N + 1);
    for(int i = 1; i < N; i++) {
        cin >> u >> v >> w;
        in[i] = u, out[i] = v;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    dfs_node_ordering(1, 0, 1);
    head[1] = channel[1] = 1;
    hld(1, 0);

    Segtree * seg = new Segtree(4 * N);
    for(int node = 2; node <= N; node++) {
        seg->update(1, 1, N, node2idx[node], cost[node]);
    }

    cin >> M;

    int op, i, c;
    while(M--) {
        cin >> op;
        if(op == 1) {
            cin >> i >> c;
            int node = (depth[in[i]] > depth[out[i]]) ? in[i] : out[i];
            seg->update(1, 1, N, node2idx[node], c);
        }
        else {
            cin >> u >> v;
            cout << query(seg, u, v, 1, N) << "\n";
        }
    }

    return 0;
}