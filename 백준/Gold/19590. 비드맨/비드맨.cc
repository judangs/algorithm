#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int N;
    cin >> N;
    
    ll total = 0, maxc = 0;
    for(int i = 1; i <= N; i++) {
        ll x; 
        cin >> x;
        total += x; 
        maxc = max(maxc, x);
    }

    ll other = total - maxc;
    
    ll answer = (maxc > other) ? (maxc - other) : total % 2;
    cout << answer << endl;

}