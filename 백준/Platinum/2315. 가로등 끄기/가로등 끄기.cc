#include <iostream>
#include <vector>
#include <cmath>
#include <memory.h>

#define INF 1e18

using namespace std;
typedef long long ll;

int N, M;
ll dp[1001][1001][2];
struct Lamp {
    int d;
    int w;
};
vector<Lamp> lamps;
vector<ll> psum;

ll off(int l, int r, int state) {

    if(l == 1 && r == N) return 0;

    ll & ret = dp[l][r][state];
    if(ret != -1) return ret;

    ret = INF;

    int now = (state == 0) ? l : r;
    ll tw = psum[l - 1] + psum[N] - psum[r];

    if(1 <= l - 1) ret = min<ll>(ret, off(l - 1, r, 0) + tw * abs(lamps[now].d - lamps[l - 1].d));
    if(r + 1 <= N) ret = min<ll>(ret, off(l, r + 1, 1) + tw * abs(lamps[now].d - lamps[r + 1].d));
    
    return ret;
}


int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;
    lamps.resize(N + 1);
    psum.resize(N + 1, 0);

    for(int i=1; i<=N; i++) {
        int d, w; cin >> d >> w;
        lamps[i] = {d, w};
        psum[i] = psum[i - 1] + w;
    }

    memset(dp, -1, sizeof(dp));
    ll answer = off(M, M, 0);
    cout << answer;
}