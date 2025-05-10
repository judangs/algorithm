#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

#define MAXFLAVOR 1000000
#define INF 1e9

using namespace std;

int N, A, B, C;
vector<int> segtree;

int merge(int a, int b) {
    return (a + b);
}

int update(int node, int idx, int l, int r, int value) {
    
    if(idx < l || r < idx) return segtree[node];
    if(l == r) {
        return (segtree[node] += value);
    }

    int m = (l + r) / 2;
    return segtree[node] = merge(update(2 * node, idx, l, m, value), 
                                    update(2 * node + 1, idx, m + 1, r, value));
}

int query(int node, int l, int r, int rank) {

    if(l == r) return l;

    int m = (l + r) / 2;
    if(rank <= segtree[2 * node])
        return query(2 * node, l, m, rank);
    else
        return query(2 * node + 1, m + 1, r, rank - segtree[2 * node]);
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int size = (int) ceil(log2(MAXFLAVOR));
    segtree.resize(1 << (size + 1), 0);

    int start = (1 << size);
    int end = (1 << (size + 1)) - 1;

    cin >> N;
    for(int i=0; i<N; i++) {
        cin >> A;

        if(A == 1) {
            cin >> B;
            int candy = query(1, 0, end - start, B);
            cout << candy << "\n";  
            update(1, candy, 0, end - start, -1);
        }
        else {
            cin >> B >> C;
            update(1, B, 0, end - start, C);
        }
    }
}