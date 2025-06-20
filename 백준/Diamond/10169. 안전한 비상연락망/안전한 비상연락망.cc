#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>

#define fASTIO ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define MAXNODE 100001
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
            for(auto child: tree[node]) {
                if(pnode != child) {
                    parent[child] = node;
                    preprocessing(tree, child, node, lv + 1);
                    weight[node] += weight[child];
                }
            }
        }
        
        void decomposite(vector<vector<int>> & tree, int node, int pnode) {
            
            in[node] = ++id;
            
            std::vector<int> next;
            for(auto child: tree[node]) {
                if(child != pnode) next.push_back(child);
            }

            sort(next.begin(), next.end(), [this](int a, int b) {
                return weight[a] > weight[b];
            });

            if(!next.empty()) {
                auto heavy = next.front();
                head[heavy] = head[node];
                decomposite(tree, heavy, node);
            }
            
            for(int idx=1; idx<next.size(); idx++) {
                int child = next[idx];
                head[child] = child;
                decomposite(tree, child, node);
            }
        }

        void build(std::vector<vector<int>> & tree) {
            memset(weight, 1, sizeof(weight));
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
    int cost;
    bool use;

    bool operator<(const Edge & o) const {
        return cost < o.cost;
    }
};
vector<Edge> edges;
vector<vector<int>> adj;

struct Segtree {

    vector<int> arr;
    vector<int> lazy;
    
    void init(int sz) {
        arr.resize(4 * sz, INF);
        lazy.resize(4 * sz, INF);
    }

    void push(int node, int l, int r) {
        if(lazy[node] == INF) return;

        arr[node] = min(arr[node], lazy[node]);
        if(l != r) {
            for(auto & child: {node << 1, node << 1 | 1})
                lazy[child] = min(lazy[child], lazy[node]);
        }

        lazy[node] = INF;
    }

    void update(int node, int s, int e, int v, int l, int r)  {

        push(node, l, r);

        if(r < s || e < l) return;
        if(s <= l && r <= e) {
            lazy[node] = min(lazy[node], v);
            push(node, l, r);
            return;
        }

        int m = (l + r) / 2;
        update(node << 1, s, e, v, l, m), update(node << 1 | 1, s, e, v, m + 1, r);
        arr[node] = min(arr[node << 1], arr[node << 1 | 1]);
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
    
    fASTIO
    cin >> N >> M;
    adj.resize(N + 1);

    for(int i=0; i<M; i++) {
        int u, v, c; cin >> u >> v >> c;
        edges.push_back({i, u, v, c, false});
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

    vector<ll> answer(M);
    for(auto & [idx, u, v, cost, use]: edges) {
        if(!use) answer[idx] = mst;
        else {
            int alter = query(u, v);
            if(alter == INF) answer[idx] = -1;
            else answer[idx] = (mst - cost + alter);
        }
    }

    for(auto ans: answer) {
        cout << ans << "\n";
    }
}
