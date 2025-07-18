#include <iostream>
#include <algorithm>

#define MAXDAY 100001
#define MAXDISH 11

using namespace std;

int N, M, V;
int dp[MAXDISH][MAXDAY];
int dessert[MAXDISH][MAXDAY];

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    
    cin >> N >> M;
    for(int i=1; i<=M; i++) {
        for(int j=1; j<=N; j++) {
            cin >> V; dessert[i][j] = V;
        }
    }

    for(int i=1; i<=M; i++) dp[i][1] = dessert[i][1];
    
    for(int day=2; day<=N; day++) {
        for(int before=1; before<=M; before++) {
            for(int after=1; after<=M; after++) {
                if(before == after) dp[after][day] = max(dp[after][day], dp[before][day - 1] + dessert[after][day] / 2);
                else dp[after][day] = max(dp[after][day], dp[before][day - 1] + dessert[after][day]);
            }
        }
    }

    int answer = 0;
    for(int dish=1; dish<=M; dish++) answer = max(answer, dp[dish][N]);

    cout << answer << endl;
    
}