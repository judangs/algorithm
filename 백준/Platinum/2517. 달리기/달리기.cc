#include <iostream>
#include <vector>
#include <algorithm>

#define MAXSZ 500001

using namespace std;
typedef pair<int, int> pii;

int N;

struct SegTree {

    vector<int> arr;
    
    SegTree() : arr(4 * MAXSZ, 0) { }

    void update(int node, int l, int r, int num) {
        if(num < l || num > r) return;
        if(l == r && l == num) {
            arr[node]++;
            return;
        }

        int m = (l + r) / 2;
        update(2 * node, l, m, num); update(2 * node + 1, m + 1, r, num);
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

auto ordering = [](const pii & l, const pii & r) {
    return l.second < r.second;
};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;
    vector<pair<int, int>> player(N);
    for(int i=0; i<N; i++) {
        int ability; cin >> ability;
        player[i] = {i, ability};
    }

    sort(player.begin(), player.end(), ordering);

    vector<pair<int, int>> order(N);
    order[0] = { 1, player.front().first };
    for(int rank=1, index=1; index < N; index++) {
        if(player[index - 1].second == player[index].second)
            order[index] = { rank, player[index].first };
        else
            order[index] = { ++rank, player[index].first };
    }

    sort(order.begin(), order.end(), ordering);

    for(int i=0, now = 1; i<N; i++, now++) {
        int rank = now - seg.query(1, 0, N, 0, order[i].first - 1);
        seg.update(1, 0, N, order[i].first);
        cout << rank << "\n";
    }

}