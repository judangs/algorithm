#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;

int N, M;
int chart[21][301];
int dp[21][301];

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;
    for(int i=1; i<=N; i++) {

        int amount; cin >> amount;
        for(int j=1; j<=M; j++) {
            cin >> chart[j][amount];
        }
    }

    for(int company=1; company<=M; company++) {
        for(int usage=0; usage<=N; usage++) {
            dp[company][usage] = dp[company - 1][usage];

            for(int amount=1; amount <= usage; amount++)
                dp[company][usage] = max(dp[company][usage], 
                                            dp[company - 1][usage - amount] + chart[company][amount]);
        }
    }

    int answer = dp[M][N];
    cout << answer << endl;

    
    vector<int> invest(M + 1, 0);
    for(int company=M, balance = N; 0 < company && 0 < balance;) {

        if(dp[company][balance] == dp[company - 1][balance]) {
            company--;
        }            
        else {
            for(int amount=1; amount <= balance; amount++) {    
                if(0 <=balance - amount) {
                    if(dp[company][balance] == dp[company - 1][balance - amount] + chart[company][amount]) {
                        invest[company] = amount;
                        company--; balance -= amount;
                        break;
                    }   
                }             
            }
        }
    }

    for(int company = 1; company <= M; company++)
        cout << invest[company] << " ";
    cout << endl;

    

}