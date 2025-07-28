#include <iostream>
#include <cmath>
#include <numeric>
#include <vector>

using namespace std;

const int MAXN = 30000000;

vector<bool> is_prime(MAXN + 1, true);

void build() {
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i * i <= MAXN; i++) {
        if(is_prime[i]) {
            for(int j = i * i; j <= MAXN; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    
    build();
    
    int n;
    cin >> n;
    
    while(n--) {
        double a, b;
        cin >> a >> b;
        
        long long scale = 1000000;
        long long p = (long long)(a * scale + 0.5);
        long long q = (long long)(b * scale + 0.5);
        
        long long g = gcd(p, q);
        p /= g;
        q /= g;

        if(p == 1) {
            p *= 2, q *= 2;
        }
        
        if(p <= MAXN && q <= MAXN && is_prime[p] && is_prime[q]) {
            cout << p << " " << q << "\n";
        } else {
            cout << "impossible\n";
        }
    }
}