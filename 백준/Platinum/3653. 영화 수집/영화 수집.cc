#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int C, N, M, Q;

void update(vector<int> & segtree, int node, int l, int r, int idx, int val) {
    if(idx < l || r < idx) return;
    if(l == r && l == idx) {
        segtree[node] = val;
        return;
    }
    
    int m = (l + r) / 2;
    update(segtree, 2 * node, l, m, idx, val);
    update(segtree, 2 * node + 1, m + 1, r, idx, val);

    segtree[node] = segtree[2 * node] + segtree[2 * node + 1];
}


int query(vector<int> & segtree, int node, int l, int r, int s, int e) {
    if(r < s || e < l) return 0;
    if(s <= l && r <= e) return segtree[node];

    int m = (l + r) / 2;
    return segtree[node] = query(segtree, 2 * node, l, m, s, e) +
                                query(segtree, 2 * node + 1, m + 1, r, s, e);
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> C;
    while(C--) {
        cin >> N >> M;

        int depth = (int) ceil(log2(N + M));
        int size = (1 << (depth + 1));

        vector<int> segtree(size, 0);
        vector<int> movies(N + 1);
        
        int s = (1 << depth), e = size - 1;
        int ptr = 0;
        for(int idx=N; idx > 0; idx--) {
            update(segtree, 1, 0, (e - s), ptr, 1);
            movies[idx] = ptr++;
        }

        for(int q=0; q<M; q++) {
            cin >> Q;
            cout << query(segtree, 1, 0, (e - s), movies[Q] + 1, (e - s)) << " ";

            update(segtree, 1, 0, (e - s), movies[Q], 0);
            update(segtree, 1, 0, (e - s), ptr, 1);

            movies[Q] = ptr++;
        }

        cout << "\n";
        
    }

}