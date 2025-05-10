#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef long long ll;

int N, M, K;
int a, b, c;
ll d;

vector<ll> segtree;
vector<ll> lazy;

void build(int node, int l, int r, int start, int end) {
    if(r < start || end < l) return;
    if(l == r) return;

    int m = (l + r) / 2;
    build(2 * node, l, m, start, end);
    build(2 * node + 1, m + 1, r, start, end);

    segtree[node] = segtree[2 * node] + segtree[2 * node + 1];
}

void lazy_update(int node, int l, int r) {
    if(lazy[node] != 0) {
        segtree[node] += (r - l + 1) * lazy[node];

        if(r != l) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }

        lazy[node] = 0;
    }
}

void update(int node, int l, int r, int start, int end, ll val) {

    lazy_update(node, l, r);

    if(r < start || end < l) return;
    if(start <= l && r <= end) {
        segtree[node] += (r - l + 1) * val;
        
        if(l != r) {
            lazy[2 * node] += val;
            lazy[2 * node + 1] += val;
        }

        return;
    }

    int m = (l + r) / 2;
    update(2 * node, l, m, start, end, val);
    update(2 * node + 1, m + 1, r, start, end,  val);

    segtree[node] = segtree[2 * node] + segtree[2 * node + 1];
}

long long query(int node, int l, int r, int start, int end) {

    lazy_update(node, l, r);
    
    if(r < start || end < l) return 0ll;
    if(start <= l && r <= end) return segtree[node];

    int m = (l + r) / 2;
    return query(2 * node, l, m, start, end) +
                query(2 * node + 1, m + 1, r, start, end);
    
} 

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> M >> K;

    int depth = ceil(log2(N));
    int size = (1 << (depth + 1));

    segtree.resize(size, 0);
    lazy.resize(size, 0);

    int s = (1 << depth), e = size - 1;
    for(int idx=s; idx <s + N; idx++) {
        cin >> segtree[idx];
    }

    build(1, 0, e - s, 0, e - s);

    for(int i=0; i<M + K; i++) {
        cin >> a;
        if(a == 1) {
            cin >> b >> c >> d;
            update(1, 0, (e - s), b - 1, c - 1, d);
        }
        else {
            cin >> b >> c;
            cout << query(1, 0, (e - s), b - 1, c - 1) << "\n";
        }
    }
    
}