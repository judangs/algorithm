#include <iostream>
#include <vector>

using namespace std;

int T, K;

int main() {
    
    cin >> T;
    while(T--) {
        cin >> K;
        
        vector<int> arr(K);
        vector<int> prefix;
        prefix.push_back(0);
        
        for(int idx=0; idx<K; idx++) {
            cin >> arr[idx];
            prefix.push_back(prefix.back() + arr[idx]);
        }
        
        vector<vector<int>> dp(K, vector<int>(K, 1e9));
        for(int idx=0; idx<K; idx++) {
            dp[idx][idx] = arr[idx];
        }
        
        for(int idx=0; idx<K - 1; idx++) {
            dp[idx][idx + 1] = (arr[idx] + arr[idx + 1]);
        }
        
        for(int length=3; length<=K; length++) {
            for(int start=0; start + length - 1 < K; start++) {
                int end = start + length - 1;
                for(int middle=start; middle < end; middle++) {
                    int next;
                    
                    if(start == middle) next = dp[middle + 1][end];
                    else if(middle + 1 == end) next = dp[start][middle];
                    else next = dp[start][middle] + dp[middle + 1][end];
                    
                    int presum = prefix[end + 1] - prefix[start];
                
                    dp[start][end] = min(dp[start][end], next + presum);
                }
            }
        }
        
        
        cout << dp[0][K - 1] << endl;
    }
}