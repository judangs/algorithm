#include <iostream>
#include <numeric>
#include <cstdlib>

using namespace std;
typedef long long ll;

int N;
ll M = 0ll;
ll balance = 0ll, minb = 1e18;

void failure() {
    cout << "-1" << endl;
    exit(0);
}

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;
    bool remain = true;
    for(int i=1; i<=N; i++) {
        ll a, b; cin >> a >> b;
        if(a > 0) {
            if(balance + a == b) balance = b;
            else
                failure();
        }
        else {

            ll recharge = b - a - balance;

            if(balance + a >= 0) {
                if(balance + a != b) failure();
                if(0 < recharge) failure();
            }
            if(balance + a < 0) {
                
                if(b != 0) minb = min(minb, b);

                if(recharge <= 0) failure();
                M = (M == 0 ? recharge : gcd(M, recharge));

                if(minb != 1e18 && M <= minb) failure();
                if(M == 1 && 0 < b) failure();
            }

            balance = b;
        }
    }

    ll answer = (M == 0 ? 1 : M);
    cout << answer << endl;

}