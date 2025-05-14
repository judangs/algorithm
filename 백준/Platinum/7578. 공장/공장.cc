#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>

#define MAXNODE 500000

using namespace std;

typedef long long ll;

int N, A, B;
unordered_map<int, int> num2idx;
vector<ll> segtree;

void update(int node, int l, int r, int idx, ll val) {
    if(l == r && l == idx) {
        segtree[node]++;
        return;
    }
    if(idx < l || r < idx) return;
    if(l == r) return;
    
    int m = (l + r) / 2;
    update(2 * node, l, m, idx, val);
    update(2 * node + 1, m + 1, r, idx, val);
    
    segtree[node] = segtree[2 * node] + segtree[2 * node + 1];
}


ll query(int node, int l, int r, int s, int e) {
    if(l > e || r < s) return 0;
    if(s <= l && r <= e) return segtree[node];

    int m = (l + r) / 2;
    return query(2 * node, l, m, s, e) + query(2 * node + 1, m + 1, r, s ,e);
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;
    for(int idx=0; idx<N; idx++) {
        cin >> A;
        num2idx[A] = idx;
    }

    vector<int> machine(N);
    for(int idx=0; idx<N; idx++) {
        cin >> B;
        machine[num2idx[B]] = idx;
    }


    int depth  = (int) ceil(log2(N));
    int size = (1 << (depth + 1));
    segtree.resize(size, 0);

    int s = (1 << depth), e = size - 1;

    ll answer = 0;
    for(int idx=0; idx<N; idx++) {
        update(1, 0, (e - s), machine[idx], 1ll);
        answer += query(1, 0, (e - s), machine[idx] + 1, (e - s));
    }

    cout << answer;

}