#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define MAXSAFE 500001

using namespace std;
typedef unsigned int ui;

int N, Q, S, E;
vector<int> adj[MAXSAFE];


struct SegTree {

    vector<ui> arr;
    vector<ui> lazysum, lazymul;
    
    void init(int sz) {
        arr.resize(4 * sz, 0);
        lazysum.resize(4 * sz, 0);
        lazymul.resize(4 * sz, 0);
    }

    void push(int node, int l, int r) {
        if(lazysum[node] == 0 && lazymul[node] == 1) return;
        arr[node] *= lazymul[node];
        arr[node] += (r - l + 1) * lazysum[node];

        if(l != r) {
            lazymul[2 * node] *= lazymul[node];
            lazysum[2 * node] *= lazymul[node];
            lazysum[2 * node] += lazysum[node];

            lazymul[2 * node + 1] *= lazymul[node];
            lazysum[2 * node + 1] *= lazymul[node];
            lazysum[2 * node + 1] += lazysum[node];            
        }

        lazysum[node] = 0, lazymul[node] = 1;
    }

    void update(int node, int l, int r, int s, int e, ui sum, ui mul) {

        push(node, l, r);

        if(r < s || e < l) return;
        if(s <= l && r <= e) {

            arr[node] *= mul, arr[node] += (r - l + 1) * sum;
            if(l != r) {
                lazymul[2 * node] *= mul;
                lazysum[2 * node] *= mul;
                lazysum[2 * node] += sum;

                lazymul[2 * node + 1] *= mul;
                lazysum[2 * node + 1] *= mul;
                lazysum[2 * node + 1] += sum;
            }

            return;
        }

        int m = (l + r) / 2;
        update(2 * node, l, m, s, e, sum, mul), update(2 * node + 1, m + 1, r, s, e, sum, mul);
        arr[node] = (arr[2 * node] + arr[2 * node + 1]);
    }

    ui query(int node, int l, int r, int s, int e) {

        push(node, l, r);
        if(r < s || e < l) return 0;
        if(s <= l && r <= e) return arr[node];

        int m = (l + r) / 2;
        return (query(2 * node, l, m, s, e) 
                    + query(2 * node + 1, m + 1, r, s, e));

    }
}seg;


struct HLD {

    int node2idx[MAXSAFE];
    int depth[MAXSAFE];
    int parent[MAXSAFE];
    int top[MAXSAFE];
    int weight[MAXSAFE];
    int in[MAXSAFE], out[MAXSAFE];

    int id = 0;
    

    void preprocessing(int node, int pnode, int lv) {

        depth[node] = lv;
        weight[node] = 1;

        for(auto child: adj[node]) {
            if(child != pnode) {
                parent[child] = node;
                preprocessing(child, node, lv + 1);
                weight[node] += weight[child];
            }
        }
    }  

    void decomposite(int node, int pnode) {

        vector<int> children;
        for(auto child: adj[node]) {
            if(child != pnode) children.push_back(child);
        }

        sort(children.begin(), children.end(), [this](int l, int r) {
            return weight[l] > weight[r];
        });

        in[node] = ++id;
        node2idx[node] = in[node];

        if(!children.empty()) {
            auto heavy = children.front();
            top[heavy] = top[node];
            decomposite(heavy, node);
        }

        for(int idx=1; idx<children.size(); idx++) {
            int child = children[idx];
            top[child] = child;
            decomposite(child, node);            
        }

        out[node] = id;
        
    }

    void update_plus(int u, int v, ui cost) {
        while(top[u] != top[v]) {
            if(depth[top[u]] > depth[top[v]]) swap(u, v);
            int vt = top[v];
            seg.update(1, 1, N, node2idx[vt], node2idx[v], cost, 1);
            v = parent[vt];
        }

        if(depth[u] > depth[v]) swap(u, v);
        seg.update(1, 1, N, node2idx[u], node2idx[v], cost, 1);
    }

    void update_multiply(int u, int v, int mul) {
        while(top[u] != top[v]) {
            if(depth[top[u]] > depth[top[v]]) swap(u, v);
            int vt = top[v];
            seg.update(1, 1, N, node2idx[vt], node2idx[v], 0, mul);
            v = parent[vt];
        }

        if(depth[u] > depth[v]) swap(u, v);
        seg.update(1, 1, N, node2idx[u], node2idx[v], 0, mul);
    }

    ui query(int u, int v) {

        ui ret = 0;

        while(top[u] != top[v]) {
            if(depth[top[u]] > depth[top[v]]) swap(u, v);
            int vt = top[v];
            ret += seg.query(1, 1, N, node2idx[vt], node2idx[v]);
            v = parent[vt];
        }

        if(depth[u] > depth[v]) swap(u, v);
        ret += seg.query(1, 1, N, node2idx[u], node2idx[v]);        
        return ret;
    }

    
}hld;


int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    
    cin >> N >> Q;
    for(int i=1; i<N; i++) {
        cin >> S >> E;
        adj[S].push_back(E), adj[E].push_back(S);
    }

    seg.init(N);
    hld.preprocessing(1, 0, 1);
    hld.top[1] = 1;
    hld.decomposite(1, 0);

    ui op, X, Y, V;
    while(Q--) {

        cin >> op;
        switch (op)
        {
        case 1:
            cin >> X >> V;
            seg.update(1, 1, N, hld.in[X], hld.out[X], V, 1);
            break;
        case 2:
            cin >> X >> Y >> V;
            hld.update_plus(X, Y, V);
            break;
        case 3:
            cin >> X >> V;
            seg.update(1, 1, N, hld.in[X], hld.out[X], 0, V);
            break;
        case 4:
            cin >> X >> Y >> V;
            hld.update_multiply(X, Y, V);
            break;
        case 5:
            cin >> X;
            cout << seg.query(1, 1, N, hld.in[X], hld.out[X]) << "\n";
            break;
        case 6:
            cin >> X >> Y;
            cout << hld.query(X, Y) << "\n";
            break;
        }
    }
}