#include <iostream>
#include <vector>
#include <algorithm>

#define MAXSZ 100000

using namespace std;
typedef pair<int, int> pii;
typedef long long ll;

int N, S;
struct SegTree {

    vector<int> arr;

    SegTree() : arr(4 * MAXSZ) { }

    void update(int node, int l, int r, int rank, int val) {
        if(rank < l || r < rank) return;
        if(l == r && l == rank) {
            arr[node] += val; return;
        }

        int m = (l + r) / 2;
        update(2 * node, l, m, rank, val);
        update(2 * node + 1, m + 1, r, rank, val);
        arr[node] = arr[2 * node] + arr[2 * node + 1];
    }

    int query(int node, int l, int r, int s, int e) {
        if(r < s || e < l) return 0;
        if(s <= l && r <= e) return arr[node];

        int m = (l + r) / 2;
        return (query(2 * node, l, m, s, e) + 
                    query(2 * node + 1, m + 1, r, s, e));
        
    }

}seg;

auto compare = [](const pii & l, const pii & r) {
    if(l.second == r.second)
        return l.first > r.first;
    return l.second < r.second;
};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> S;
    vector<pair<int, int>> lamp(N);
    for(int i=0; i<N; i++) {
        int light; cin >> light;
        lamp[i] = { i, light };
    }

    sort(lamp.begin(), lamp.end(), compare);
    vector<pair<int, int>> order(N);
    order[0] = { 1, lamp.front().first };

    for(int idx = 1, rank = 1; idx < N; idx++) {
        order[idx] = { ((lamp[idx - 1].second == lamp[idx].second ) 
                            ? rank : ++rank) , lamp[idx].first};
    }

    sort(order.begin(), order.end(), [](const pii & l, const pii & r) {
        return l.second < r.second;
    });

    int left = 0, right = left;
    ll now = 0;
    while(right < S) {
        int inversion = seg.query(1, 0, N, 0, order[right].first - 1);
        now += inversion;
        seg.update(1, 0, N, order[right].first, 1);
        right++;
    }

    ll answer = now;
    for(; right < N; right++, left++) {
        
        now -= seg.query(1, 0, N, order[left].first + 1, N);
        seg.update(1, 0, N, order[left].first, -1);
        
        int inversion = seg.query(1, 0, N, 0, order[right].first - 1);
        now += inversion;
        seg.update(1, 0, N, order[right].first, 1);

        answer = max(answer, now);
    }

    cout << answer << endl;

}