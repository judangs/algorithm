#include <iostream>

using namespace std;
typedef long long ll;

int N, K;
ll M;

int student[100001];
int dp[31][100001];

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> K >> M;
    for(int i=1; i<=N; i++) cin >> student[i];
    for(int i=1; i<=K; i++) cin >> dp[0][i];

    for(int d=1; d<=30; d++)
        for(int i=1; i<=K; i++) 
            dp[d][i] = dp[d - 1][dp[d - 1][i]];

    for(int i=1; i<=N; i++) {
        int media = student[i];
        for(int k=30; k>=0; k--)
            if((1ll << k) & (M - 1)) media = dp[k][media];

        cout << media << " ";
    }

}