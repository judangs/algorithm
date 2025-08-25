#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <climits>

#define MAXPRIME 1000000

using namespace std;
typedef long long ll;

int T;
vector<bool> is_prime(MAXPRIME + 1, true);

void build_prime_tbl() {
    is_prime[1] = false;
    for(int num = 2; num <= MAXPRIME; num++) {
        if(is_prime[num]) {
            for(long long next = (long long)num * num; next <= MAXPRIME; next += num)
                is_prime[next] = false;
        }
    }
}

int main() {
    build_prime_tbl();

    cin >> T;
    while(T--) {
        ll n, k; 
        cin >> n >> k;
        
        map<ll, ll> pcount;
        
        for(int num = 2; num <= MAXPRIME && (ll)num * num <= k; num++) {
            if(is_prime[num]) {
                ll count = 0;
                while(k % num == 0) {
                    count++;
                    k /= num;
                }
                if(count > 0)
                    pcount[num] = count;
            }
        }

        if(k > 1) pcount[k] = 1;
        
        ll answer = LLONG_MAX;
        for(auto & [prime, exp]: pcount) {
            ll count = 0, now = n;
            while(prime <= now) {
                count += now / prime;
                now /= prime;
            }
            answer = min(answer, count / exp);
        }

        cout << answer << endl;        
    }
}