#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>

#define MAXNODE 100001
#define MAXEDGE 300001
#define INF 1e9

using namespace std;

namespace unionfind {
    int pnode[MAXNODE];

    void init(int sz) {
        for(int node=1; node<=sz; node++) pnode[node] = node;
    }

    int find(int node) {
        if(node == pnode[node]) return node;
        return (pnode[node] = find(pnode[node]));
    }

    bool merge(int a, int b) {
        a = find(a), b = find(b);
        if(a == b) return false;
        if(a < b) swap(a, b);
        pnode[a] = b;
        return true;
    }
}

namespace hld {
    int depth[MAXNODE];
    int parent[MAXNODE];
    int weight[MAXNODE];
    int head[MAXNODE];
    int in[MAXNODE];

    int id = 0;
    
    struct HLD {
        
        void preprocessing(vector<vector<int>> & tree, int node, int pnode, int lv) {

            depth[node] = lv;
            weight[node] = 1;

            for(auto & child: tree[node]) {
                if(pnode != child) {
                    parent[child] = node;
                    preprocessing(tree, child, node, lv + 1);
                    weight[node] += weight[child];
                    if(weight[child] > weight[tree[node].front()]) swap(child, tree[node].front());
                }
            }
        }
        
        void decomposite(vector<vector<int>> & tree, int node, int pnode) {
            
            in[node] = ++id;
            
            int heavy = 0;
            for(auto child: tree[node]) {
                if(child != pnode) {
                    if(!heavy) {
                        heavy = child;
                        head[heavy] = head[node];
                        decomposite(tree, heavy, node);
                    }
                    else {
                        head[child] =child;
                        decomposite(tree, child, node);
                    }
                }
            }
        }

        void build(std::vector<vector<int>> & tree) {
            head[1] = 1;

            preprocessing(tree, 1, 0, 1);
            decomposite(tree, 1, 0);
        }
        
    }hld;
}

using namespace unionfind;
using namespace hld;
typedef long long ll;


int N, M;
ll mst = 0ll;
struct Edge {
    int idx;
    int u;
    int v;
    ll cost;
    bool use;

    bool operator<(const Edge & o) const {
        return cost < o.cost;
    }
};
vector<Edge> edges;
vector<vector<int>> adj;

ll answer[MAXEDGE];

struct Segtree {
    int arr[1 << 18], lazy[1 << 18];
    
    void init(int sz) {
        memset(arr, 0x3f, sizeof(arr)), memset(lazy, 0x3f, sizeof(lazy));
    }

    void push(int node, int l, int r) {
        arr[node] = min(arr[node], lazy[node]);
        if(l != r) {
            for(auto & child: {node << 1, node << 1 | 1})
                lazy[child] = min(lazy[child], lazy[node]);
        }
    }

    void update(int node, int s, int e, int v, int l, int r)  {

        push(node, l, r);

        if(r < s || e < l) return;
        if(s <= l && r <= e) {
            lazy[node] = v;
            push(node, l, r);
            return;
        }

        int m = (l + r) / 2;
        update(node << 1, s, e, v, l, m), update(node << 1 | 1, s, e, v, m + 1, r);
    }

    int query(int node, int s, int e, int l, int r) {

        push(node, l, r);
        if(r < s || e < l) return INF;
        if(s <= l && r <= e) return arr[node];

        int m = (l + r) / 2;
        return min(query(node << 1, s, e, l, m), query(node << 1 | 1, s, e, m + 1, r));   
    }

}seg;


void update(int u, int v, int cost) {
    while(head[u] != head[v]) {
        if(depth[head[u]] < depth[head[v]]) swap(u, v);
        seg.update(1, in[head[u]], in[u], cost, 1, N);
        u = parent[head[u]];
    }

    if(depth[u] > depth[v]) swap(u, v);
    seg.update(1, in[u] + 1, in[v], cost, 1, N);
}

int query(int u, int v) {

    int ret = INF;
    while(head[u] != head[v]) {
        if(depth[head[u]] < depth[head[v]]) swap(u, v);
        ret = min(ret, seg.query(1, in[head[u]], in[u], 1, N));
        u = parent[head[u]];
    }

    if(depth[u] > depth[v]) swap(u, v);
    ret = min(ret, seg.query(1, in[u] + 1, in[v], 1, N));   
    return ret; 
}


int main() {
    
    ios::sync_with_stdio(false); 
    cin.tie(0), cout.tie(0);
    cin >> N >> M;

    adj.resize(N + 1);
    edges.resize(M);

    for(int i=0; i<M; i++) {
        int u, v, c; cin >> u >> v >> c;
        edges[i] = {i, u, v, c, false};
    }

    unionfind::init(N);
    sort(edges.begin(), edges.end());
    for(auto & [idx, u, v, cost, use]: edges) {
        if(merge(u, v)) {
            mst += cost;
            use = true;
            adj[u].push_back(v), adj[v].push_back(u);
        }
    }

    hld::hld.build(adj);
    seg.init(N);
    
    for(auto & [idx, u, v, cost, use]: edges) {
        if(!use) update(u, v, cost);
    }

    for(auto & [idx, u, v, cost, use]: edges) {
        if(!use) answer[idx] = mst;
        else {
            ll alter = query(u, v);
            if(alter == INF) answer[idx] = -1;
            else answer[idx] = (mst - cost + alter);
        }
    }

    for(int i=0; i<M; i++) cout << answer[i] << "\n";
}
