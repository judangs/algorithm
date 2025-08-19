#include <iostream>
#include <memory.h>

using namespace std;

int n, p, q;
string dealer[500];
string p1[500], p2[500];
int cache[500][500][500];


int play(int d, int l, int r) {
    
    if(d == n) return 0;

    int & ret = cache[d][l][r];
    if(ret != -1) return ret;

    ret = 0;

    ret = max(ret, play(d + 1, l, r));
    if(l + 1 < p) ret = max(ret, play(d, l + 1, r));
    if(r + 1 < q) ret = max(ret, play(d, l, r + 1));
    if(l < p && p1[l] == dealer[d]) ret = max(ret, 1 + play(d + 1, l + 1, r));
    if(r < q && p2[r] == dealer[d]) ret = max(ret, 1 + play(d + 1, l, r +  1));
    
    return ret;

}


int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> p >> q;
    for(int i=0; i<n; i++) cin >> dealer[i];
    for(int i=0; i<p; i++) cin >> p1[i];
    for(int i=0; i<q; i++) cin >> p2[i];

    memset(cache, -1, sizeof(cache));

    int answer = play(0, 0, 0);
    cout << answer << endl;

}