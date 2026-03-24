#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;
typedef long long ll;

int N;
ll C;

struct Node {
    int pos;
    ll value;

    bool operator>(const Node & o) const {
        return pos > o.pos;
    }

    bool operator<(const Node & o) const {
        return pos < o.pos;
    }    
};

int main() {

    fastio;

    priority_queue<Node, vector<Node>, greater<Node>> xq;
    priority_queue<Node, vector<Node>, less<Node>> yq;
    
    cin >> N >> C;
    for(int i = 0; i < N; i++) {
        int X, Y; ll V; cin >> X >> Y >> V;
        xq.push({ X, V });
        yq.push({ Y, V});
    }

    ll ans = 0ll, now = 0ll; int count = 0;
    while(!yq.empty() && !xq.empty()) {
        if(count < C) {
            now += xq.top().value; xq.pop();
            ans = max(ans, now);
            count++;
        }
        else {
            int ty = yq.top().pos, ycount = 0;
            ll ytot = 0ll;
            while(!yq.empty() && yq.top().pos == ty) {
                ytot += yq.top().value;
                yq.pop();
                ycount++;
            }

            count = max(0, count - ycount);
            now = max(0ll, now - ytot);
        }
    }
    
    cout << ans << '\n';

}