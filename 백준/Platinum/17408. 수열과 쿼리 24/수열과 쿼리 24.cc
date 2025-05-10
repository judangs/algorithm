#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#define INF 1e9

using namespace std;

int N, A, M;
int o, i, v, l, r;

vector<pair<int, int>> segtree;

pair<int, int> merge(pair<int, int> a, pair<int, int> b) {
    vector<int> arr = {a.first, a.second, b.first, b.second};
    sort(arr.rbegin(), arr.rend());
    
    return {arr[0], arr[1]};
}

pair<int, int> update(int node, int idx, int l, int r, int val) {

    if(idx < l || r < idx) return segtree[node];
    if(l == r) {
        return (segtree[node] = {val, 0});
    }

    int m = (l + r) / 2;
    return (segtree[node] = merge(update(2 * node, idx, l, m, val), 
                                    update(2 * node + 1, idx, m + 1, r, val)));
}


int query(int left, int right) {

    vector<int> parts;
    while(left <= right) {
        if(left % 2 == 1) {
            parts.push_back(segtree[left].first);
            parts.push_back(segtree[left].second);
            left++;
        }
        if(right % 2 == 0) {
            parts.push_back(segtree[right].first);
            parts.push_back(segtree[right].second);
            right--;
        }

        left /= 2;
        right /= 2;
    }


    sort(parts.rbegin(), parts.rend());
    return (parts[0] + parts[1]);
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    cin >> N;


    int p = ceil(log2(N));
    segtree.resize(1 << (p + 1), {0, 0});

    int left = pow(2, p), right = pow(2, p + 1) - 1;
    for(int idx=left; idx < left + N; idx++) {
        cin >> A;
        update(1, idx - left, 0, right - left, A);
    }
    
    cin >> M;

    for(int idx=0; idx<M; idx++) {
        cin >> o;
        if(o == 1) {
            cin >> i >> v;
            update(1, i - 1, 0, right - left, v);
        }
        else {
            cin >> l >> r;
            cout << query(left + (l - 1), left + (r - 1)) << "\n";
        }
    }

}