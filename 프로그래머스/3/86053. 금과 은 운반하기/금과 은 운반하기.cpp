#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

bool is_valid(long long time, int a, int b, vector<int> & g, vector<int> & s, vector<int> & w, vector<int> & t) {
    
    int n = g.size();
    long long gold = 0ll, silver = 0ll, total = 0ll;
    for(int i = 0; i < n; i++) {
        long long count = time / (2 * t[i]);
        if((long long) t[i] <= (time % (2ll * (long long)t[i]))) count++;
        long long tot = (long long) w[i] * count;
        
        gold += min((long long) g[i], tot);
        silver += min((long long) s[i], tot);
        total += min((long long ) g[i] + (long long) s[i], tot);
    }
    
    return (a <= gold && b <= silver && (a + b) <= total);
    
}


long long solution(int a, int b, vector<int> g, vector<int> s, vector<int> w, vector<int> t) {
    
    
    long long lo = 0ll, hi = 1e16;
    while(lo + 1 < hi) {
        long long mid = (lo + hi) / 2ll;
        if(is_valid(mid, a, b, g, s, w, t))
            hi = mid;
        else
            lo = mid;
    }
    
    long long ans = hi;
    return ans;
    
}