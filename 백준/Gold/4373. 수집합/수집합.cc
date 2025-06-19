#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>

using namespace std;

const int INF = -INT32_MIN;

int N, S;
struct Node {
    int num;
    int lo;
    int hi;

    bool operator<(const Node & o) const {
        return num < o.num;
    }

    bool operator!=(const Node & o) const {
        return !((lo == o.lo) || (lo == o.hi) || (hi == o.lo) || (hi == o.hi));
    }
};

int solved(int p, int q, vector<Node> & add, vector<Node> & sub) {

    if(p == add.size() || q == sub.size()) return INF;
    int ret = INF;

    if(add[p].num < sub[q].num) ret = max(ret, solved(p + 1, q, add, sub));
    if(add[p].num > sub[q].num) ret = max(ret, solved(p, q + 1, add, sub));

    if(add[p].num == sub[q].num) {
        if(add[p] != sub[q]) ret = max(ret, sub[q].lo);
        
        if(p < q) ret = max(ret, solved(p + 1, q, add, sub));
        else ret = max(ret, solved(p, q + 1, add, sub));  
    }

    return ret;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    while(cin >> N) {
        if(N == 0) break;

        vector<int> number;
        for(int i=0; i<N; i++) {
            cin >> S;
            number.push_back(S);
        }

        vector<Node> add, sub;
        for(int i=0; i<N; i++) {
            for(int j=0; j<N; j++) {
                if(i == j) continue;

                int lo = number[i], hi = number[j];

                int sum = lo + hi;
                int diff = lo - hi;

                add.push_back({sum, lo, hi});
                sub.push_back({diff, lo, hi});
            }
        }

        sort(add.begin(), add.end());
        sort(sub.begin(), sub.end());

        N = add.size();
        
        int answer = solved(0, 0, add, sub);

        if(answer == INF) cout << "no solution\n";
        else cout << answer << "\n";
    }
}