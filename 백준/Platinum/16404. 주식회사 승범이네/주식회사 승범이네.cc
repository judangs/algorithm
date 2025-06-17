#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
typedef long long ll;

int N, M, p;
int nodeidx = 0;

vector<vector<int>> adj;
vector<pair<int, int>> ett;
vector<ll> lazy;
vector<ll> segtree;

void lazy_update(int node, int l, int r) {
    if(lazy[node] != 0) {
        segtree[node] += (r - l + 1) * lazy[node];

        if(l != r) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }

        lazy[node] = 0;
    }
}

void update(int node, int l, int r, int s, int e, int v) {
    lazy_update(node, l, r);
    
    if(r < s || e < l) return;
    
    if(s <= l && r <= e) {
        lazy[node] += v;
        lazy_update(node, l, r);
        return;
    }

    int m = (l + r) / 2;
    update(2 * node, l, m, s, e, v);
    update(2 * node + 1, m + 1, r, s, e, v);
    
    lazy_update(2 * node, l, m);
    lazy_update(2 * node + 1, m + 1, r);
    segtree[node] = segtree[2 * node] + segtree[2 * node + 1];
}

ll query(int node, int l, int r, int idx) {
    lazy_update(node, l, r);
    
    if(l == r) {
        return segtree[node];
    }
    
    int m = (l + r) / 2;
    if(idx <= m) {
        return query(2 * node, l, m, idx);
    } else {
        return query(2 * node + 1, m + 1, r, idx);
    }
}

void build_ett_array(int node, int parent) {
    ett[node].first = ++nodeidx;
    
    for(auto child: adj[node]) {
        if(child != parent) {
            build_ett_array(child, node);
        }
    }

    ett[node].second = nodeidx;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;

    int depth = ceil(log2(N));
    int sz = (1 << (depth + 1));
    
    segtree.resize(sz, 0);
    lazy.resize(sz, 0);
    adj.resize(N + 1);
    ett.resize(N + 1);

    for(int i = 1; i <= N; i++) {
        cin >> p;
        if(p == -1) continue;
        adj[i].push_back(p);
        adj[p].push_back(i);
    }
    
    build_ett_array(1, 0);

    int op, i, w;
    while(M--) {
        cin >> op;
        if(op == 1) {
            cin >> i >> w;
            update(1, 1, N, ett[i].first, ett[i].second, w);
        }
        else {
            cin >> i;
            cout << query(1, 1, N, ett[i].first) << "\n";
        }
    }

    return 0;
}