#include <iostream>
#include <vector>
#include <algorithm>

#define MAXTIME 100001
#define INF 1e9

using namespace std;

int T, N;
struct Cookie {
    int ovenl, ovenr;
};


int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    
    cin >> T;
    while(T--) {

        cin >> N;
        vector<Cookie> cookies(N + 1);
        for(int i=1; i<=N; i++) {
            int a, b; cin >> a >> b;
            cookies[i] = {a, b};
        }

        vector<vector<int>> dp(2, vector<int>(MAXTIME, INF));
        dp[1][cookies[1].ovenl] = 0;
        dp[1][0] = cookies[1].ovenr;

        for(int idx=2; idx <= N; idx++) {

            int now = idx % 2, prev = (idx - 1) % 2;
            fill(dp[now].begin(), dp[now].end(), INF);

            for(int time=0; time < MAXTIME; time++) {
                auto & cookie = cookies[idx];
                if(dp[prev][time] != INF) dp[now][time] = min(dp[now][time], dp[prev][time] + cookie.ovenr);
                if(0 <= time - cookie.ovenl) dp[now][time] = min(dp[now][time], dp[prev][time - cookie.ovenl]);
            }
        }

        int answer = INF;
        for(int time=0; time < MAXTIME; time++) {
            if(dp[N % 2][time] != INF)
                answer = min(answer, max(time, dp[N % 2][time]));
        }

        cout << answer << endl;

    }
}