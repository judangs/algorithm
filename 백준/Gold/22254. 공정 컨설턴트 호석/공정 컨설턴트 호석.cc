#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;

int N, X;
vector<int> gift;
struct Node {
    int idx;
    long long usage;
};

struct compare {
    bool operator()(const Node & l, const Node & r) const {
        return l.usage > r.usage;
    }
};

bool valid(int count) {

    priority_queue<Node, vector<Node>, compare> pq;
    for(int i = 0; i < count; i++)
        pq.push({ i, 0ll });
    

    for(auto g: gift) {
        auto node = pq.top(); pq.pop();
        pq.push({ node.idx, node.usage + g});
    }

    long long time = 0ll;
    while(!pq.empty()) {
        time = max(time, pq.top().usage);
        pq.pop();
    }

    return time <= X;

}

int main() {

    fastio;

    cin >> N >> X;
    gift = vector<int>(N);
    for(auto & time: gift) cin >> time;

    int lo = 1, hi = N;
    while(lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if(valid(mid)) hi = mid;
        else
            lo = mid;
    }

    int ans = valid(lo) ? lo: hi;
    cout << ans << "\n";


}