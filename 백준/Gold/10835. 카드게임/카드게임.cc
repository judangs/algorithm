#include <iostream>
#include <memory.h>
#include <vector>
#include <algorithm>

using namespace std;

int N;
int cache[2001][2001];
vector<int> lpad, rpad;


int solver(int lp, int rp) {
    
    if(lp == N || rp == N) return 0;
    if(cache[lp][rp] != -1) return cache[lp][rp];

    int & ret = cache[lp][rp];
    ret = 0;
    
    if(lpad[lp] > rpad[rp]) 
        ret = max(ret, solver(lp, rp + 1) + rpad[rp]);
    ret = max({ret, solver(lp + 1, rp), solver(lp + 1, rp + 1)});    

    return ret;
}


int main() {

    memset(cache, -1, sizeof(cache));

    cin >> N;
    lpad.resize(N), rpad.resize(N);

    for(int i=0; i<N; i++) cin >> lpad[i];
    for(int i=0; i<N; i++) cin >> rpad[i];

    cout << solver(0, 0);


    
}