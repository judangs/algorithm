#include <iostream>
#include <vector>
#include <algorithm>

#define INF 1e18

using namespace std;

typedef long long ll;

int n, m;

vector<vector<ll>> cache(10001, vector<ll>(101, -1));

ll cutting(int x, int y) {

    if(x == y) return cache[x][y] = 1;
    if(x % y == 0) return cache[x][y] = x / y;

    if(cache[x][y] != -1) return cache[x][y];
    
    ll & ret = cache[x][y] = x * y;
    if(x > 3 * y) { // x > k * y => k(?)
        ret = min(ret, cutting(x - y, y) + 1);   
        return ret; 
    }

    for(int sub=1; sub<x; sub++) {
        if(x - sub > 0)
            ret = min(ret, cutting(sub, y) + cutting(x - sub, y));
    }
    
    for(int sub=1; sub<y; sub++) {
        if(y - sub > 0)
            ret = min(ret, cutting(x, sub) + cutting(x, y - sub));
    }


    return ret;
}

int main() {
    cin >> n >> m;

    if(n < m) swap(n, m);
    
    ll answer = cutting(n, m);
    cout << answer;
}