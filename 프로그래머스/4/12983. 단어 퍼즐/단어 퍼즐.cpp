#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

vector<int> dp;
set<string> words;

int solution(vector<string> strs, string t) {
    
    for(string str: strs) {
        words.insert(str);
    }
    
    dp.resize(t.size(), 1e9);
    for(int current=1; current<=t.size(); current++) {
        int idx = current - 1;
        for(int prev=current-1; prev >= current - 5 && 0 <= prev; prev--) {
            string part = t.substr(prev, current - prev);
            if(words.find(part) != words.end()) {
                if(prev == 0) {
                    dp[idx] = 1;
                } 
                else {
                    if(dp[prev - 1] != 1e9) {
                        dp[idx] = min(dp[idx], dp[prev - 1] + 1);
                    }    
                }
            }
        }
    }
    
    return (dp[dp.size() - 1] != 1e9 ? dp[dp.size() - 1] : -1);
    
    
}