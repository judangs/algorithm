#include <iostream>
#include <vector>
#include <cstring>

#define MOD 10007

using namespace std;

string S;

int cache[1001][1001];

int main() {

    cin >> S;

    int n = S.size();
    
    for(int idx=0; idx<n; idx++)
        cache[idx][idx] = 1;
    
    for(int idx=0; idx<n-1; idx++) {
        if(S[idx] == S[idx + 1]) cache[idx][idx + 1] = 3;
        else cache[idx][idx + 1] = 2;
    }

    for(int len=3; len<=n; len++) {
        for(int left=0; left + len - 1 <n; left++) {
            int right = left + len - 1;

            if(S[left] == S[right]) cache[left][right] = (cache[left + 1][right] + cache[left][right - 1] + 1) % MOD;
            else cache[left][right] = (cache[left + 1][right] + cache[left][right - 1] - cache[left + 1][right - 1] + MOD) % MOD;
        }
    }

    cout << cache[0][n - 1];
}