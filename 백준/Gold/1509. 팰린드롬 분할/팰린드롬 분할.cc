#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<bool>> palindrome;
vector<int> dp;

int solve(string s) {
    palindrome.resize(s.size(), vector<bool>(s.size(), false));

    for(int idx=0; idx<s.size(); idx++) {
        palindrome[idx][idx] = true;
    }

    for(int idx=0; idx<s.size()-1; idx++) {
        if(s[idx] == s[idx + 1])
            palindrome[idx][idx + 1] = true;
    }

    for(int k=2; k<s.size(); k++) {
        for(int start=0; start + k <s.size(); start++) {
            int end = start + k;
            if(s[start] == s[end] && palindrome[start + 1][end - 1] == true) {
                palindrome[start][end] = true;
            }
        }
    }

    int N = s.size();
    dp.resize(N + 1, 1e9);
    dp[0] = 0;

    for(int end=0; end<N; end++) {
        for(int start=0; start<=end; start++) {
            if(palindrome[start][end] == true) {
                dp[end + 1] = min(dp[end + 1], dp[start] + 1);
            }
        }
    }

    return dp[N];
}

int main() {
    string arr;
    cin >> arr;
    cout << solve(arr);

}