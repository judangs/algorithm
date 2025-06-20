#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

const ll INF = -1e18;
int N, Q, U, V;

struct Node {
    ll lmax;
    ll rmax;
    ll max;
    ll all;
};

template <typename T, int sz>
class SegTree {
    
    private:
        vector<T> arr;

    public:

        SegTree(): arr(sz << 1, Node{INF, INF, INF, 0}) { }

        Node merge(const Node & l, const Node & r) {
            Node node{INF, INF, INF, INF};
            node.lmax = max(l.lmax, l.all + r.lmax);
            node.rmax = max(r.rmax, r.all + l.rmax);
            node.max = max({l.max, r.max, l.rmax + r.lmax});
            node.all = l.all + r.all;

            return node;
        }

        void update(int node, int l, int r, int idx, int v) {
            if(idx < l || r < idx) return;
            if(l == r && l == idx) {
                arr[node] = {v, v, v, v};
                return;
            }

            int m = (l + r) / 2;
            update(node << 1, l, m, idx, v), update(node << 1 | 1, m + 1, r, idx, v);
            arr[node] = merge(arr[node << 1], arr[node << 1 | 1]);
        }

        Node query(int node, int s, int e, int l, int r) {
            if(r < s || e < l) return {INF, INF, INF, 0};
            if(s <= l && r <= e) return arr[node];
            
            int m = (l + r) / 2;
            return merge(query(node << 1, s, e, l, m),
                            query(node << 1 | 1, s, e, m + 1, r));
        }
};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    SegTree<Node, 1 << 17> seg;
    cin >> N >> Q >> U >> V;
    for(int i=1; i<=N; i++) {
        int K; cin >> K;
        seg.update(1, 1, N, i, U * K + V);
    }

    while(Q--) {
        ll A, B, C; cin >> C >> A >> B;
        if(C) seg.update(1, 1, N, A, U * B + V);
        else {
            auto node = seg.query(1, A, B, 1, N);
            cout << (node.max - V) << "\n";
        }
    }
}