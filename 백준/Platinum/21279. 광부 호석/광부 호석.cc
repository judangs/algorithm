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
    int x;
    int y;
    ll value;
};

struct GreaterCompare {
    bool operator()(const Node & l, const Node & r) {
        if(l.x == r.x)
            return l.y < r.y;
        return l.x > r.x;
    }
};

struct LessCompare {
    bool operator()(const Node & l, const Node & r) {
        if(l.y == r.y)
            return l.x > r.x;
        return l.y < r.y;
    }
};    

    int main() {

        fastio;

        priority_queue<Node, vector<Node>, GreaterCompare> xq;
        priority_queue<Node, vector<Node>, LessCompare> yq;
        
        cin >> N >> C;
        for(int i = 0; i < N; i++) {
            int X, Y; ll V; cin >> X >> Y >> V;
            xq.push({ X, Y, V }); yq.push({ X, Y, V});
        }

        ll ans = 0ll, now = 0ll; int count = 0;
        int H = 100001, W = -1;
        while(0 <= H && W <= 100000) {
    
            if(count < C) {
                now += xq.top().value; count++;
                xq.pop();
                W = (xq.empty() ? 100000 + 1 : xq.top().x);
            }
            
            else if(count >= C) {
                now -= yq.top().value; 
                yq.pop();
                H = (yq.empty() ? -1 : yq.top().y);
                count--;
            }

            ans = max(ans, now);

        }
        
        cout << ans << '\n';

    }