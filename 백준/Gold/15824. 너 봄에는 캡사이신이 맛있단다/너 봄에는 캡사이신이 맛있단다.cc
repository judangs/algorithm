#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <memory.h>

#define MAXMENU 300001
#define MOD 1000000007

using namespace std;
typedef long long ll;


int N;
vector<ll> scoville;
ll powtwo[MAXMENU];

void build_pow_num_two_table() {
    
    memset(powtwo, 0, sizeof(powtwo));
    powtwo[0] = 1;
    for(int idx=1; idx<MAXMENU; idx++)
        powtwo[idx] = (powtwo[idx - 1] * 2) % MOD;
    
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    
    cin >> N;
    scoville.resize(N);
    for(int i=0; i<N; i++) cin >> scoville[i];
        
    build_pow_num_two_table();
    sort(scoville.begin(), scoville.end());

    ll answer = 0ll;
    for(int idx=0; idx<N; idx++) {
        ll maxcomb = (scoville[idx] * powtwo[idx]) % MOD;
        ll mincomb = (scoville[idx] * powtwo[N - 1 - idx]) % MOD;

        answer += (maxcomb - mincomb + MOD) % MOD;
        answer %= MOD;
    }
    
    cout << answer;
}