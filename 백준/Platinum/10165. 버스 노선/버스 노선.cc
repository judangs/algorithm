#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

ll N, M;
ll a, b;

struct Node {
    int bus;
    ll start;
    ll end;
};

vector<Node> station;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;
    for(int idx=1; idx<=M; idx++) {
        cin >> a >> b;
        if(a < b) {
            station.push_back({ idx, a, b });
            station.push_back({ idx, a + N, b + N});
        }
        else {
            if(b == 0) station.push_back({ idx, a + N, 2 * N});
            else station.push_back({ idx, a, b + N});
        }
    }

    sort(station.begin(), station.end(), [](const Node & l, const Node & r) {
        if(l.start == r.start)
            return l.end > r.end;
        return l.start < r.start;
    });

    vector<bool> alive(M + 1, true);

    ll end = station.front().end;
    for(int idx=1; idx<station.size(); idx++) {
        auto & node = station[idx];
        if(node.end <= end) {
            alive[node.bus] = false;
        }

        end = max(end, node.end);
    }

    for(int idx=1; idx<=M; idx++) {
        if(alive[idx])
            cout << idx << " ";
    }

}