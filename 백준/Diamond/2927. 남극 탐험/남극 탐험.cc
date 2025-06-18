#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define MAXLAND 30001

using namespace std;
typedef long long ll;

int N, Q, p;
int id, nodeid = 1;

int node2idx[MAXLAND];
int depth[MAXLAND];
int weight[MAXLAND];
int head[MAXLAND];
int parent[MAXLAND];

vector<int> land;
vector<vector<int>> adj;

struct Query {
    string op;
    int A, B; 
};
vector<Query> queries;

struct UnionFind {
    int sz;
    int parent[MAXLAND];

    UnionFind(int _sz): sz(_sz) {
        for(int node=1; node<=sz; node++) parent[node] = node;
    }

    void init() {
        for(int node=1; node<=sz; node++) parent[node] = node;
    }

    int find(int node) {
        if(parent[node] == node) return node;
        return parent[node] = find(parent[node]);
    }

    bool merge(int u, int v) {
        u = find(u), v = find(v);
        if(u == v) return false;
        if(u > v) parent[u] = v;
        else parent[v] = u;
        return true;
    }
};

struct Segtree {
    vector<ll> arr;

    Segtree(int sz) {
        arr.resize(4 * sz, 0ll);
    }  

    void update(int node, int l, int r, int idx, int val) {
        if(idx < l || r < idx) return;
        if(l == r && idx == l) {
            arr[node] = val;
            return;
        }

        int m = (l + r) / 2;
        update(2 * node, l, m, idx, val), update(2 * node + 1, m + 1, r, idx, val);
        arr[node] = arr[2 * node] + arr[2 * node + 1];        
    }

    ll query(int node, int l, int r, int start, int end) {
        if(r < start || end < l) return 0;
        if(start <= l && r <= end) return arr[node];
        
        int m = (l + r) / 2;
        return (query(2 * node, l, m, start, end) + 
                    query(2 * node + 1, m + 1, r, start, end));
    }
};

ll query_travel_path(Segtree * seg, int u, int v) {

    ll ret = 0;
    while(head[u] != head[v]) {
        if(depth[head[u]] > depth[head[v]]) swap(u, v);
        int vt = head[v];
        ret += seg->query(1, 1, N, node2idx[vt], node2idx[v]);
        v = parent[vt];        
    }

    
    if(depth[u] > depth[v]) swap(u, v);
    ret += seg->query(1, 1, N, node2idx[u], node2idx[v]);
    return ret;
}

void dfs_node_ordering(int node, int pnode, int lv) {

    depth[node] = lv;
    weight[node] = 1;

    for(auto child: adj[node]) {
        if(child != pnode) {
            parent[child] = node;
            dfs_node_ordering(child, node, lv + 1);
            weight[node] += weight[child];
        }
    }
}

void hld(int node, int pnode) {

    node2idx[node] = nodeid++;

    vector<int> children;
    for(auto child: adj[node]) {
        if(child != pnode) {
            children.push_back(child);
        }
    }

    sort(children.begin(), children.end(), [](int l, int r) {
        return weight[l] > weight[r];
    });

    if(!children.empty()) {
        auto heavy = children.front();
        head[heavy] = head[node];
        hld(heavy, node);
    }

    for(int idx=1; idx<children.size(); idx++) {
        int child = children[idx];
        head[child] = child;
        hld(child, node);
    }
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;

    UnionFind * uf = new UnionFind(N);
    Segtree * seg = new Segtree(N);
    adj.resize(N + 1);
    land.resize(N + 1);

    for(int i=1; i<=N; i++) cin >> land[i];

    cin >> Q;
    
    while(Q--) {
        string op;
        int a, b;
        cin >> op >> a >> b;
        queries.push_back({op, a, b});
        if(op == "bridge") {
            if(uf->merge(a, b)) {
                adj[a].push_back(b), adj[b].push_back(a);       
            }
        }
    }

    for(int node=1; node<=N; node++) {
        if(uf->merge(1, node)) {
            adj[1].push_back(node), adj[node].push_back(1);
        }
    }

    head[1] = 1;
    dfs_node_ordering(1, 0, 1);
    hld(1, 0);
    
    uf->init(); 
    for(int node=1; node<=N; node++) {
        seg->update(1, 1, N, node2idx[node], land[node]);
    }

    for(auto query: queries) {
        if(query.op == "bridge") {
            if(uf->merge(query.A, query.B)) cout << "yes\n";
            else cout << "no\n";
        }
        if(query.op == "penguins") {
            seg->update(1, 1, N, node2idx[query.A], query.B);
        }
        if(query.op == "excursion") {
            if(uf->find(query.A) == uf->find(query.B)) cout << query_travel_path(seg, query.A, query.B) << "\n";
            else cout << "impossible\n";
        }
    }

}