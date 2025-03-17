#include <iostream>
#include <vector>

#define DIV 1000000007

using namespace std;

int N, M, P;

vector<vector<long long>> dp;

int main() {
    cin >> N >> M >> P;
    dp.resize(P + 1, vector<long long>(N + 1 ,0));

    dp[1][1] = N;
    for(int pick=2; pick<=P; pick++) {
        for(int type=1; type<=N; type++) {
            dp[pick][type] += (dp[pick - 1][type - 1] * (N - type + 1) % DIV);
            if(type >= M) {
                dp[pick][type] += (dp[pick - 1][type] * (type - M) % DIV);
            }
        }     
    }

    cout << (dp[P][N] % DIV);
}