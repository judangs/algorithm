#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int T, ry, rx;
ll K;
ll W[5][5];

bool pass(ll cost) {

    vector<ll> goal(5, 0); vector<ll> most(5, 0);
    vector<pair<int, int>> rank(4);
    
    W[ry][rx] = cost;
    
    for(int i=1; i<=4; i++) {
        rank[i - 1] = {i, 0};
        for(int j=1; j<=4; j++) {
            if(i != j) {
                goal[i] += W[i][j] - W[j][i];
                most[i] += W[i][j];
            }
        }
    }
    

    for(int i=1; i<=4; i++) {
        for(int j=i+1; j<=4; j++) {
            if(W[i][j] > W[j][i]) {
                rank[i-1].second += 3;
            } else if(W[i][j] < W[j][i]) {
                rank[j-1].second += 3;
            } else {
                rank[i-1].second += 1;
                rank[j-1].second += 1;
            }
        }
    }

    W[ry][rx] = -1;

    sort(rank.begin(), rank.end(), [&](const pii & l, const pii & r) {
        if(l.second == r.second) {
            if(goal[l.first] == goal[r.first]) {
                if(most[l.first] == most[r.first])
                    return l.first < r.first;
                return most[l.first] > most[r.first];
            }
            return goal[l.first] > goal[r.first];
        }
        return l.second > r.second;
    });

    int r = find_if(rank.begin(), rank.end(), [](const pii & e) {
        return e.first == T;
    }) - rank.begin();

    return (r < 2);
}

int main() {

    cin >> T >> K;
    for(int i=1; i<=4; i++) {
        for(int j=1; j<=4; j++) {
            cin >> W[i][j];
            if(W[i][j] == -1) {
                ry = i, rx = j;
            }
        }
    }

    if(!pass(K)) 
        cout << -1 << endl;
    else {
        ll lo = 0ll, hi = K;
        while(lo < hi) {
            ll mid = (lo + hi) / 2;
            if(pass(mid)) 
                hi = mid;
            else
                lo = mid + 1;
        }
        cout << lo << endl;
    }
    
}