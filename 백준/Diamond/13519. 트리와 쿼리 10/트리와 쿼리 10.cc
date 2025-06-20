#include <iostream>
#include <vector>
#include <algorithm>

#define MAXNODE 100001
#define ISLOWER(x) std::max(0ll, x);

using namespace std;
typedef long long ll;


const ll INF = -1e18;
int N, M;
int w[MAXNODE];

vector<int> adj[MAXNODE];

struct Node {
    ll lmax;
    ll rmax;
    ll max;
    ll all;

    Node() { 
        lmax = rmax = max = all = 0ll;
    }

    Node(ll _l, ll _r, ll _m, ll _a): lmax(_l), rmax(_r), max(_m), all(_a) { }

    void constraint() {
        lmax = ISLOWER(lmax);
        rmax = ISLOWER(rmax);
        max = ISLOWER(max);
    }
};


namespace tree {

    template<typename T, int sz>
    class SegTree {
        private:
        
            vector<T> arr;
            vector<ll> lazy;

        public:

            SegTree(): arr(sz << 1), lazy(sz << 1, INF) { }

            Node merge(const Node & l, const Node & r) {
                Node node;
                node.lmax = max(l.lmax, l.all + r.lmax);
                node.rmax = max(r.rmax, r.all + l.rmax);
                node.max = max({l.max, r.max, l.rmax + r.lmax});
                node.all = (l.all + r.all);
                node.constraint();
                return node;
            }

            void push(int node, int l, int r) {
                if(lazy[node] != INF) {
                    arr[node].all = (r - l + 1) * lazy[node];
                    arr[node].lmax = arr[node].rmax = arr[node].max = max(0ll, arr[node].all);
                    
                    if(l != r) {
                        for(const int child: {node << 1, node << 1 | 1}) 
                            lazy[child] = lazy[node];
                    }
                    
                    lazy[node] = INF;
                }
            }

            void update(int node, int l, int r, int s, int e, ll v) {

                push(node, l, r);
                if(r < s || e < l) return;
                if(s <= l && r <= e) {
                    lazy[node] = v;
                    push(node, l, r);
                    return;
                }

                int m = (l + r) / 2;
                update(node << 1, l, m, s, e, v), update(node << 1 | 1, m + 1, r, s, e, v);
                arr[node] = merge(arr[node << 1], arr[node << 1 | 1]);
            }

            Node query(int node, int l, int r, int s, int e) {

                push(node, l, r);
                if(r < s || e < l) return {0, 0, 0, 0};
                if(s <= l && r <= e) return arr[node];

                int m = (l + r) / 2;
                return merge(query(node << 1, l, m, s, e), 
                                query(node << 1 | 1, m + 1, r, s, e));
            }
            


    };

    SegTree<Node, 1 << 17> seg;
}

namespace solution {

    int depth[MAXNODE];
    int weight[MAXNODE];
    int parent[MAXNODE];
    int head[MAXNODE];
    int in[MAXNODE];

    class HLD {
        private:
            int id = 0;
            int root = 1;

        public:
            
            HLD() {
                head[root] = root;
                preprocessing(root, 0, 1);
                decomposite(root, 0);
            }

            void preprocessing(int node, int pnode, int lv) {
                
                depth[node] = lv;
                weight[node] = 1;
                
                for(auto & child: adj[node]) {
                    if(child != pnode) {
                        parent[child] = node;
                        preprocessing(child, node, lv + 1);
                        weight[node] += weight[child];
                    }
                }
            }

            void decomposite(int node, int pnode) {

                in[node] = ++id;

                sort(adj[node].begin(), adj[node].end(), [](int a, int b) {
                    return weight[a] > weight[b];
                });

                int heavy = 0;
                for(auto child: adj[node]) {
                    if(child != pnode) {
                        if(!heavy) {
                            heavy = child;
                            head[heavy] = head[node];
                            decomposite(heavy, node);
                        }
                        else {
                            head[child] = child;
                            decomposite(child, node);
                        }
                    }
                }

                tree::seg.update(1, 1, N, in[node], in[node], w[node]);
            }
    };
    
}

using namespace solution;


void update(int u, int v, ll weight) {

    while(head[u] != head[v]) {
        if(depth[head[u]] < depth[head[v]]) swap(u, v);
        tree::seg.update(1, 1, N, in[head[u]], in[u], weight);
        u = parent[head[u]];
    }

    if(depth[u] > depth[v]) swap(u, v);
    tree::seg.update(1, 1, N, in[u], in[v], weight);
}

ll query(int u, int v) {

    Node forward, backward;

    while(head[u] != head[v]) {
        if(depth[head[u]] > depth[head[v]]) {
            auto node = tree::seg.query(1, 1, N, in[head[u]], in[u]);
            forward = tree::seg.merge(node, forward);
            u = parent[head[u]];
        }
        else {
            auto node = tree::seg.query(1, 1, N, in[head[v]], in[v]);
            backward = tree::seg.merge(node, backward);
            v = parent[head[v]];
        }
    }

    
    if(depth[u] <= depth[v]) {
        auto node = tree::seg.query(1, 1, N, in[u], in[v]);    
        backward = tree::seg.merge(node, backward);
    }
    else {
        auto node = tree::seg.query(1, 1, N, in[v], in[u]);    
        forward = tree::seg.merge(node, forward);
    }

    swap(forward.lmax, forward.rmax);
    return tree::seg.merge(forward, backward).max;
}



int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    
    cin >> N;
    for(int node=1; node<=N; node++)
        cin >> w[node];

    for(int i=1; i<N; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v), adj[v].push_back(u);
    }

    HLD hld;

    cin >> M;
    while(M--) {
        int op, u, v; cin >> op;
        if(op == 1) {
            cin >> u >> v;
            cout << query(u, v) << "\n";
        }
        else {
            ll wei;
            cin >> u >> v >> wei;
            update(u, v, wei);
        }
    }
    
    
}