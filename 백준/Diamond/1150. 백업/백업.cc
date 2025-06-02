#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef long long ll;

int n, k, s;
vector<int> company;

struct Node {
    int left;
    int right;
    ll distance;
};

struct compare {
    bool operator()(const Node & l, const Node & r) {
        return l.distance > r.distance;
    }
};

priority_queue<Node, vector<Node>, compare> pq;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> k;
    for(int i=0; i<n; i++) {
        cin >> s;
        company.push_back(s);
    }

    for(int idx=1; idx<n; idx++) {
        pq.push({idx - 1, idx, company[idx] - company[idx - 1]});
    }

    vector<bool> visit(n, false);
    vector<int> lnode(n), rnode(n);
    vector<int> ldistance(n), rdistance(n);

    for(int idx=0; idx<n; idx++) {
        lnode[idx] = idx - 1;
        rnode[idx] = idx + 1;

        if(0 <= idx - 1) ldistance[idx] = company[idx] - company[idx - 1];
        if(idx + 1 < n) rdistance[idx] = company[idx + 1] - company[idx];
    }

    long long answer = 0ll;
    while(!pq.empty() && k != 0) {
        auto node = pq.top();
        pq.pop();
        
        if(!visit[node.left] && !visit[node.right]) {
            answer += node.distance;
            visit[node.left] = true, visit[node.right] = true;

            k--;

            if(0 <= lnode[node.left] && rnode[node.right] < n) {
                ll d = ldistance[node.left] + rdistance[node.right] - node.distance;
                pq.push({lnode[node.left], rnode[node.right], d});

                rdistance[lnode[node.left]] = d;
                ldistance[rnode[node.right]] = d;

                lnode[rnode[node.right]] = lnode[node.left];
                rnode[lnode[node.left]] = rnode[node.right];
            }
        }    
    }

    cout << answer;   
}