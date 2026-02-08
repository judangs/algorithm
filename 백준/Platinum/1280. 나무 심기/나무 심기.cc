#include <iostream>
#include <vector>

#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define DIV 1000000007

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;

constexpr int MAX_POS = 200000;

pii operator+(const pii &l, const pii &r) {
    return { l.first + r.first, l.second + r.second };
}

struct SegTree {

    vector<pii> arr;

    SegTree() : arr(4 * MAX_POS + 5, {0, 0}) {}

    void insert(int node, int l, int r, int idx) {
        if (idx < l || r < idx) return;

        if (l == r) {
            arr[node].first += 1;
            arr[node].second += idx;
            return;
        }

        int m = (l + r) / 2;
        insert(node * 2, l, m, idx);
        insert(node * 2 + 1, m + 1, r, idx);

        arr[node] = arr[node * 2] + arr[node * 2 + 1];
    }

    pii query(int node, int l, int r, int s, int e) {
        if (r < s || e < l) return {0, 0};
        if (s <= l && r <= e) return arr[node];

        int m = (l + r) / 2;
        return query(node * 2, l, m, s, e)
             + query(node * 2 + 1, m + 1, r, s, e);
    }
};

int main() {
    fastio;

    int n;
    cin >> n;

    vector<int> position(n);
    for (auto &p : position) cin >> p;

    SegTree seg;

    ll ans = 1;

    for (int i = 0; i < n; i++) {
        int A = position[i];

        pii left  = seg.query(1, 0, MAX_POS, 0, A - 1);
        pii right = seg.query(1, 0, MAX_POS, A + 1, MAX_POS);

        ll cost = (ll)A * left.first - left.second
                + right.second - (ll)A * right.first;

        if (i > 0) {
            cost %= DIV;
            ans = (ans * cost) % DIV;
        }

        seg.insert(1, 0, MAX_POS, A);
    }

    cout << ans << '\n';
}
