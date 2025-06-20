#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

const int INF = -1e9;
int N, M, A;

struct Node {
    int lmax;
    int rmax;
    int max;
    int all;
};

template <typename T, int sz>
class SegTree {
    
    private:
        T arr[sz << 1];

    public:

        SegTree() {
            fill(arr, arr + (sz << 1), Node{INF, INF, INF, INF});
        }

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
    cin >> N;
    for(int i=1; i<=N; i++) {
        cin >> A;
        seg.update(1, 1, N, i, A);
    }

    cin >> M;
    while(M--) {
        int i, j; cin >> i >> j;
        auto node = seg.query(1, i, j, 1, N);
        int answer = max({node.lmax, node.rmax, node.max, node.all});
        cout << answer << "\n";
    }
}