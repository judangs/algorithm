#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int N;

vector<int> segtree;

void update(int node, int l, int r, int idx, int v) {
    if(idx < l || r < idx) return;
    if(l == r && l == idx) {
        segtree[node] = v;
        return;
    }

    int m = (l + r) / 2;
    update(2 * node, l, m, idx, v);
    update(2 * node + 1, m + 1, r, idx, v);
    segtree[node] = segtree[2 * node] + segtree[2 * node + 1];
}

int query(int node, int l, int r, int s, int e) {
    if(r < s || e < l) return 0;
    if(s <= l && r <= e) return segtree[node];

    int m = (l + r) / 2;
    return query(2 * node, l, m, s, e) + 
                query(2 * node + 1, m + 1, r, s, e);

}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;
    segtree.resize(4 * N);
    vector<string> flow(N);
    for(int i=0; i<N; i++) cin >> flow[i];

    sort(flow.begin(), flow.end());

    vector<pair<string, int>> rev;
    for(int idx=0; idx<N; idx++) {
        auto & word = flow[idx];
        reverse(word.begin(), word.end());
        rev.push_back({word, idx + 1});
    }

    sort(rev.begin(), rev.end(), [](pair<string, int> & l, pair<string, int> & r) {
        return l.first < r.first;
    });

    long long answer = 0;
    for(int idx=0; idx<N; idx++) {
        auto & word = rev[idx];
        answer += query(1, 1, N, word.second + 1, N);
        update(1, 1, N, word.second, 1);
    }

    cout << answer << endl;

}