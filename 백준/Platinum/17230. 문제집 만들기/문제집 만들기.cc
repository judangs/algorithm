#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

#define MAXPROBLEM 100000

#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;

const int inf = 1e9;
int N, M, Q;
set<int> solved[MAXPROBLEM + 1];

template<typename T>
class SegTree {

    private:    
        int init;
        vector<T> arr;
        function<T(T, T)> op;
    
    public:
        SegTree(int init, function<T(T, T)> func) : init(init), arr(4 * MAXPROBLEM, init) { 
            op = func;
        }

        void update(int node, int l, int r, int idx, T val) {
            if(idx < l || r < idx) return;
            if(l == r && l == idx) {
                arr[node] = val;
                return;
            }

            int m = (l + r) / 2;
            update(2 * node, l, m, idx, val);
            update(2 * node + 1, m + 1, r, idx, val);
            arr[node] = op(arr[2 * node], arr[2 * node + 1]);
        }

        T query(int node, int l, int r, int s, int e) {
            if(r < s || e < l) return init;
            if(s <= l && r <= e) return arr[node];

            int m = (l + r) / 2;
            return op(query(2 * node, l, m, s, e), query(2 * node + 1, m + 1, r, s, e));
        }
};

SegTree<int> minseg = SegTree<int>(inf, [](int a, int b) {
    return min(a, b);
});
SegTree<int> maxseg = SegTree<int>(0, [](int a, int b) {
    return max(a, b);
});

void update(int idx, int val, SegTree<int> & seg) {
    seg.update(1, 1, N, idx, val);
}

string query(int s, int e) {

    int lo = minseg.query(1, 1, N, s, e);
    int hi = maxseg.query(1, 1, N, s, e);
    
    if(s <= lo && hi <= e) return "YES";
    return "NO";

} 

int main() {

    fastio;
    cin >> N >> M >> Q;

    for(int p = 1; p <= N; p++) {
        solved[p].insert(p);
        update(p, p, minseg); update(p, p, maxseg);
    }

    for(int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        solved[a].insert(b);
        update(a, *solved[a].begin(), minseg); update(a, *solved[a].rbegin(), maxseg);
    }

    while(Q--) {
        int w, x, y; cin >> w >> x >> y;
        if(w == 1) cout << query(x, y) << '\n';
        if(w == 2) {
            solved[x].erase(y);
            update(x, *solved[x].begin(), minseg); update(x, *solved[x].rbegin(), maxseg);
        }
        if(w == 3) {
            solved[x].insert(y);
            update(x, *solved[x].begin(), minseg); update(x, *solved[x].rbegin(), maxseg);            
        }
    }

}