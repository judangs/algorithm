#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
typedef unsigned int ui;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int T;
    cin >> T;
    
    while(T--) {
        int V, D;
        cin >> V >> D;
        
        vector<int> machine(V + 1);
        for(int i = 1; i <= V; i++) {
            cin >> machine[i];
        }
        
        sort(machine.begin() + 1, machine.end());
        
        ui dp[32][32][1001];
        memset(dp, 0, sizeof(dp));
        
        dp[0][0][D] = 1;
        
        for(int item = 1; item <= V; item++) {
            for(int last = 0; last <= V; last++) {
                for(int money = 0; money <= D; money++) {
                    if(dp[item-1][last][money] == 0) continue;
                    
                    int new_last = (last == 0) ? item : last;
                    dp[item][new_last][money] += dp[item-1][last][money];
                    
                    if(money >= machine[item]) { 
                        int select_last = last;
                        dp[item][select_last][money - machine[item]] += dp[item-1][last][money];
                    }
                }
            }
        }
        
        ui answer = 0;
        for(int last = 0; last <= V; last++) {
            for(int money = 0; money <= D; money++) {
                if(money == D) continue;
                if(last == 0 || money < machine[last])
                    answer += dp[V][last][money];
                
            }
        }
        
        cout << answer << endl;
    }
}