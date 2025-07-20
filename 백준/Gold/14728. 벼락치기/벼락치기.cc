#include <iostream>
#include <algorithm>

using namespace std;

int N, T;
int dp[101][10001];

struct Problem {
    int time, score;
};
Problem exam[101];

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> T;

    for(int i=1; i<=N; i++) {
        int K, S; cin >> K >> S;
        exam[i] = {K, S};
    }

    dp[1][0] = 0, dp[1][exam[1].time] = exam[1].score;

    for(int problem=2; problem <= N; problem++) {
        for(int time=0; time <= T; time++) {
            int ptime = time - exam[problem].time;
            if(0 <= ptime)
                dp[problem][time] = max(dp[problem - 1][ptime] + exam[problem].score, dp[problem - 1][time]);
            else
                dp[problem][time] = dp[problem - 1][time];
        }
    }

    int answer = 0;
    for(int time=0; time<=T; time++) {
        answer = max(answer, dp[N][time]);
    }

    cout << answer << endl;
    
}