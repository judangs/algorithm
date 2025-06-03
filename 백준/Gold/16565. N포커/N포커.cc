#include <iostream>
#include <vector>
#include <memory.h>

#define MOD 10007

using namespace std;

int N;
int comb[53][53];

void build_combination_table() {

    memset(comb, 0, sizeof(comb));

    for(int n=0; n<=52; n++) {
        for(int r=0; r<=52 && r <= n; r++) {
            if(r == 0 || n == r) comb[n][r] = 1;
            else
                comb[n][r] = (comb[n - 1][r] + comb[n - 1][r - 1]) % MOD;
        }
    }
}

int main() {

    build_combination_table();
    cin >> N;

    int pair = N / 4;
    
    int answer = 0;
    for(int p=1; p<=pair; p++) {
        if(p % 2 == 1) answer = (answer + (comb[13][p] * comb[52 - 4 * p][N - 4 * p])) % MOD;
        else answer = (answer - (comb[13][p] * comb[52 - 4 * p][N - 4 * p] % MOD) + MOD) % MOD;
    }

    cout << answer;
}
