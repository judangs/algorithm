#include <iostream>
#include <vector>
#include <memory.h>
#include <numeric>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

int N;
ll K;
string A;

vector<int> modt(51);
vector<ll> arr, arrsz;
vector<string> strnum;
ll cache[(1 << 15)][100];

ll calc(int set, ll num) {

    if((1 << N) - 1 == set) {
        if(num == 0) return 1;
        return 0;
    }
    
    ll & ret = cache[set][num];
    if(ret != -1) return ret;
    ret = 0;

    for(int idx=0; idx<N; idx++) {
        if((set & (1 << idx)) == 0) {
            ll next = ((num * modt[arrsz[idx]]) % K) + arr[idx] % K;
            ret += calc(set | (1 << idx), next % K);
        }
    }

    return ret;
}

int main() {

    cin >> N;
    ll factorial = 1, cur = N;
    while(cur) factorial *= cur--;

    for(int i=0; i<N; i++) {
        cin >> A;
        strnum.push_back(A);
    }

    cin >> K;

    modt[0] = 1 % K;
    for(int i = 1; i <= 50; i++) {
        modt[i] = (modt[i-1] * 10) % K;
    }        

    for(auto num: strnum) {

        ll mod = 0;
        for(auto & c: num) {
            mod = (mod * 10 + (c - '0')) % K;
        }

        arr.push_back(mod % K); 
        arrsz.push_back(num.size());       
    }

    memset(cache, -1, sizeof(cache));
    ll count = calc(0, 0);

    if(count == 0) cout << "0/1";
    else if(count == factorial) cout << "1/1";
    else {
        ll _gcd = gcd(count, factorial);
        cout << count / _gcd << "/" << factorial / _gcd << "\n";
    }
}