#include <iostream>

#define INF 1e18

using namespace std;
typedef long long ll;

int L, G;
int C[8001];
ll prefix[8001];
ll dp[801][8001];

ll risk(int l, int r) {
    return (prefix[r] - prefix[l - 1]) * (r - l + 1);
}


void DnC(int person, int l, int r, int optl, int optr) {
    
    if(l > r) return;
    int m = (l + r) / 2;
    
    ll mincost = INF; int opt = -1;
    for(int k=optl; k<=min(m - 1, optr); k++) {
        ll cost = dp[person - 1][k] + risk(k + 1, m);
        if(cost < mincost) {
            mincost = cost; opt = k;
        }
    }

    dp[person][m] = mincost;

    DnC(person, l, m - 1, optl, opt);
    DnC(person, m + 1, r, opt, optr);
}

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> L >> G;
    for(int i=1; i<=L; i++) {
        cin >> C[i];
        prefix[i] = prefix[i - 1] + C[i];
    }

    for(int i=1; i<=L; i++) dp[1][i] = i * prefix[i];
    for(int g=2; g<=G; g++)
        for(int l=1; l<=g && l <= L; l++) dp[g][l] = prefix[l];

    for(int g=2; g<=G; g++)
        DnC(g, g, L, g - 1, L - 1);

    cout << dp[G][L] << endl;
    
}