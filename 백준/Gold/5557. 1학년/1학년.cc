#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;
typedef long long ll;

int N, su;
vector<int> num;
ll cache[101][21];

ll solver(int d, int ans) {
    
    if(ans < 0 || 20 < ans) return 0;
    if(d == num.size() - 1) {
        if(ans == num.back()) return 1;
        return 0;
    }
    
    ll & ret = cache[d][ans];
    if(ret != -1) return ret;

    ret = 0;

    if(d == 0) ret += solver(d + 1, ans + num[d]);
    else {
        ret += solver(d + 1, ans + num[d]);
        ret += solver(d + 1, ans - num[d]);
    }

    return ret;
}

int main() {

    memset(cache, -1, sizeof(cache));

    cin >> N;
    for(int i=0; i<N; i++) {
        cin >> su; num.push_back(su);
    }

    cout << solver(0, 0);

}