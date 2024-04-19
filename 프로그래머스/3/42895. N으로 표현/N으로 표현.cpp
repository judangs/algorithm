#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

map<int, set<int>> dp; 

void add_value(int i, int j, int k) {
    for(auto first=dp[j].begin(); first!=dp[j].end(); first++) {
        for(auto second=dp[k].begin(); second != dp[k].end(); second++) {
            dp[i].insert(*first + *second);
            dp[i].insert(*first - *second);
            dp[i].insert(*first * *second);
            if(*second != 0)
                dp[i].insert((int)(*first / *second));
        }
    }
}

int solution(int N, int number) {

    if(N == number)
        return 1;
        
    dp[1].insert(N);
    for(int i=2; i<=8; i++) {
        dp[i].insert(stoi(string(i, '0' + N)));
        for(int j=1; j<i; j++) {
            for(int k=1; k<=(i-j); k++) {
                add_value(i, j, k);
            }
        }

        if(find(dp[i].begin(), dp[i].end(), number) != dp[i].end())
            return i;
    }
    return -1;
}