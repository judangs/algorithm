#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int inf = 1e9;
int unit[100000 + 1][17] = { 0, };

int dfs(int depth, int n, vector<vector<int>> & cost, vector<int> ticket, vector<int> & price) {
    if(depth == n) return 0;
    
    int ret = inf;
    int usage = min(n - 1, ticket[depth]); 
    
    ret = min(ret, cost[depth][usage] + dfs(depth + 1, n, cost, ticket, price));
    for(int i = 0; i < ticket.size(); i++) ticket[i] += unit[depth][i];
    ret = min(ret, cost[depth][usage] + price[depth] + dfs(depth + 1, n, cost, ticket, price));    
    
    return ret;
    
}

int solution(vector<vector<int>> cost, vector<vector<int>> hint) {    
    
    int n = cost.size(), m = hint.size();
    for(int i = 0; i < m; i++) {
        for(int j = 1; j < hint[i].size(); j++)
            unit[i][hint[i][j] - 1]++;
    }
    
    vector<int> price(n, 0);
    vector<int> ticket(n, 0);
    for(int i = 0; i < m; i++) price[i] = hint[i].front();
    int ans = dfs(0, n, cost, ticket, price);
    return ans;
    
    
}