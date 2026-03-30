#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = (1LL << 60);

struct SegTree {
    struct Node {
        long long mn;   // 살아 있는 음식들 중 최소값
        long long lazy; // 구간 일괄 감소
        int alive;      // 살아 있는 음식 개수
    };

    int n;
    vector<Node> tree;

    SegTree(int sz) : n(sz), tree(4 * sz) {}

    Node merge(const Node& a, const Node& b) {
        return { min(a.mn, b.mn), 0, a.alive + b.alive };
    }

    void build(int node, int l, int r, const vector<int>& food_times) {
        if (l == r) {
            tree[node] = { food_times[l - 1], 0, 1 };
            return;
        }

        int m = (l + r) / 2;
        build(node * 2, l, m, food_times);
        build(node * 2 + 1, m + 1, r, food_times);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void apply(int node, long long v) {
        if (tree[node].mn != INF) tree[node].mn += v;
        tree[node].lazy += v;
    }

    void push(int node) {
        if (tree[node].lazy != 0) {
            apply(node * 2, tree[node].lazy);
            apply(node * 2 + 1, tree[node].lazy);
            tree[node].lazy = 0;
        }
    }

    void pull(int node) {
        tree[node].mn = min(tree[node * 2].mn, tree[node * 2 + 1].mn);
        tree[node].alive = tree[node * 2].alive + tree[node * 2 + 1].alive;
    }

    void range_add(int node, int l, int r, int s, int e, long long v) {
        if (r < s || e < l || tree[node].alive == 0) return;

        if (s <= l && r <= e) {
            apply(node, v);
            return;
        }

        push(node);
        int m = (l + r) / 2;
        range_add(node * 2, l, m, s, e, v);
        range_add(node * 2 + 1, m + 1, r, s, e, v);
        pull(node);
    }

    long long query_min() {
        return tree[1].mn;
    }

    int count_alive() {
        return tree[1].alive;
    }

    // mn == 0 인 leaf들을 모두 제거
    void erase_zero(int node, int l, int r) {
        if (tree[node].alive == 0 || tree[node].mn > 0) return;

        if (l == r) {
            tree[node] = { INF, 0, 0 };
            return;
        }

        push(node);
        int m = (l + r) / 2;
        erase_zero(node * 2, l, m);
        erase_zero(node * 2 + 1, m + 1, r);
        pull(node);
    }

    // 살아 있는 음식 중 k번째(1-based) 인덱스 찾기
    int kth(int node, int l, int r, int k) {
        if (l == r) return l;

        push(node);
        int leftAlive = tree[node * 2].alive;
        int m = (l + r) / 2;

        if (k <= leftAlive) return kth(node * 2, l, m, k);
        return kth(node * 2 + 1, m + 1, r, k - leftAlive);
    }
};

int solution(vector<int> food_times, long long k) {
    int n = food_times.size();

    long long sum = 0;
    for (int x : food_times) sum += x;
    if (sum <= k) return -1;

    SegTree seg(n);
    seg.build(1, 1, n, food_times);

    while (true) {
        int alive = seg.count_alive();
        long long mn = seg.query_min();

        if (alive == 0) return -1;

        long long cost = mn * alive;

        if (cost <= k) {
            k -= cost;
            seg.range_add(1, 1, n, 1, n, -mn); // 전체에서 mn만큼 감소
            seg.erase_zero(1, 1, n);           // 0이 된 음식 제거
        } else {
            break;
        }
    }

    int alive = seg.count_alive();
    int order = (int)(k % alive) + 1;
    return seg.kth(1, 1, n, order);
}