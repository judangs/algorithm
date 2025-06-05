#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
typedef long long ll;

int N, Q;
int x, y, a, b;
vector<ll> segtree;


void update(int node, int l, int r, int idx, int val) {
    if(idx < l || r < idx) return;
    if(l == r) {
        segtree[node] = val;
        return;
    }

    int middle = (l + r) / 2;
    update(2 * node, l, middle, idx, val);
    update(2 * node + 1, middle + 1, r, idx, val);

    segtree[node] = segtree[2 * node] + segtree[2 * node + 1];
}

ll query(int node, int l, int r, int s, int e) {
    if(r < s || e < l) return 0;
    if(s <= l && r <= e) return segtree[node];
    
    int middle = (l + r) / 2;
    return (query(2 * node, l, middle, s, e) 
            + query(2 * node + 1, middle + 1, r, s, e));
}


int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> Q;
    int depth = ceil(log2(N));
    segtree.resize(1 << (depth + 1));

    int s = 1 << depth, e = segtree.size() - 1;
    for(int idx=s; idx < s + N; idx++) {
        cin >> b;
        update(1, 0, e - s, idx - s, b);
    }

    for(int q=0; q<Q; q++) {
        cin >> x >> y >> a >> b;
        if(x > y) swap(x, y);
        cout << query(1, 0, e - s, x - 1, y - 1) << "\n";
        update(1, 0, e - s, a - 1, b);
    }
}