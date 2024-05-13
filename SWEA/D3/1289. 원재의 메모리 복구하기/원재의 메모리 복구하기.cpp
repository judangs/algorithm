#include <iostream>
#include <vector>
#include <string>

using namespace std;

int T;

int solve(string memory) {
    vector<int> dp(memory.size(), 0);
    for(int i=0; i<dp.size(); i++) {
        if(dp[i] % 2 == 0 && memory[i] == '1') {
            for(int k=i; k<dp.size(); k++) dp[k]++;
        }
        if(dp[i] % 2 == 1 && memory[i] == '0') {
            for(int k=i; k<dp.size(); k++) dp[k]++;
        }
    }

    return dp.back();
}

int main() {
    cin >> T;
    for(int i=1; i<=T; i++) {
        string memory;
        cin >> memory;
        cout << "#" << i << " " << solve(memory) << endl;
    }    
}