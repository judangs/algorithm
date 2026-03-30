#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct SegTree {
    vector<int> tree;

    SegTree(int n) : tree(4 * n, 0) {}

    void build(int node, int l, int r) {
        if (l == r) {
            tree[node] = 1; // 처음에는 모든 음식이 살아 있음
            return;
        }

        int m = (l + r) / 2;
        build(node * 2, l, m);
        build(node * 2 + 1, m + 1, r);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    void update(int node, int l, int r, int idx, int val) {
        if (idx < l || r < idx) return;

        if (l == r) {
            tree[node] = val; // 1 -> 살아 있음, 0 -> 제거됨
            return;
        }

        int m = (l + r) / 2;
        update(node * 2, l, m, idx, val);
        update(node * 2 + 1, m + 1, r, idx, val);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    int kth(int node, int l, int r, int k) {
        if (l == r) return l;

        int leftCount = tree[node * 2];
        int m = (l + r) / 2;

        if (k <= leftCount) return kth(node * 2, l, m, k);
        return kth(node * 2 + 1, m + 1, r, k - leftCount);
    }

    int alive() const {
        return tree[1];
    }
};

int solution(vector<int> food_times, long long k) {
    int n = (int)food_times.size();

    long long total = 0;
    for (int t : food_times) total += t;
    if (total <= k) return -1;

    // (음식 시간, 원래 인덱스)
    vector<pair<int, int>> foods;
    foods.reserve(n);
    for (int i = 0; i < n; i++) {
        foods.push_back({food_times[i], i});
    }
    sort(foods.begin(), foods.end());

    SegTree seg(n);
    seg.build(1, 0, n - 1);

    long long prev = 0;
    int pos = 0;

    while (pos < n) {
        long long cur = foods[pos].first;
        long long diff = cur - prev;

        if (diff > 0) {
            long long alive = seg.alive();
            long long spend = diff * alive;

            if (spend <= k) {
                k -= spend;
                prev = cur;
            } else {
                // 남아 있는 음식들 중에서 k % alive 번째 음식 찾기
                int order = (int)(k % alive) + 1; // 1-based
                int idx = seg.kth(1, 0, n - 1, order);
                return idx + 1; // 문제의 음식 번호는 1-based
            }
        }

        // 현재 레이어까지 다 먹은 음식 제거
        while (pos < n && foods[pos].first == cur) {
            seg.update(1, 0, n - 1, foods[pos].second, 0);
            pos++;
        }
    }

    return -1;
}