#include <iostream>

#define MAXDAY 100001

using namespace std;
typedef long long ll;

int N, D;
ll answer = 0ll;
ll T[MAXDAY], V[MAXDAY];

void solved(int l, int r, int optl, int optr) {
    if(l > r) return;

    int m = (l + r) / 2;
    ll maxc = -1; int opt = -1;
    for(int k=optl; k<=min(m + D, optr); k++) {
        if(k < m) continue;

        ll cost = (k - m) * T[k] + V[m];
        if(maxc < cost) {
            maxc = cost, opt = k;
        }
    }

    answer = max(answer, maxc);
    solved(l, m - 1, optl, opt);
    solved(m + 1, r, opt, optr);
}

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> D;
    for(int day=1; day<=N; day++) cin >> T[day];
    for(int day=1; day<=N; day++) cin >> V[day];
    
    solved(1, N, 1, N);
    cout << answer;

}