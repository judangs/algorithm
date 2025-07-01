#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>

#define INF 1e18

using namespace std;

int n, m, x;
bool init = false;
vector<int> basket;
long long dp[301][301][2];

long long eat(int l, int r, int state, int count) {

    if(count == 0) return 0;
    if(l > r) return 0;
    
    long long & ret = dp[l][r][state];
    if(ret != -1) return ret;

    ret = 0ll;

    int pos = (state == 0) ? l : r;
    if(0 <= l - 1) ret = max(ret, eat(l - 1, r, 0, count - 1) - count * abs(basket[pos] - basket[l - 1]) + m);
    if(r + 1 < basket.size()) ret = max(ret, eat(l, r + 1, 1, count - 1) - count * abs(basket[pos] - basket[r + 1]) + m);

    return ret;
}


int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    
    cin >> n >> m;
    
    for(int i=0; i<n; i++) {
        cin >> x; basket.push_back(x);
        if(x == 0) init = true;
    }

    if(!init) basket.push_back(0);
    sort(basket.begin(), basket.end());

    int start = find(basket.begin(), basket.end(), 0) - basket.begin();
    
    long long answer = 0;
    for(int count=1; count<=basket.size(); count++) {
        memset(dp, -1, sizeof(dp));
        if(init) 
            answer = max(answer, eat(start, start, 0, count - 1) + m);
        else 
            answer = max(answer, eat(start, start, 0, count));
    }

    cout << answer;
}