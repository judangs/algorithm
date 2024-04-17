#include <string>
#include <vector>
#include <iostream>

using namespace std;

int answer = 0;

void dfs(int n, int sum, int p) {
    if(n == sum) {
        answer++;
        return;
    }

    if(sum + p <= n) {
        dfs(n, sum + p, p + 1);
    }
}

int solution(int n) {
    
    for(int i=1; i<=n; i++) {
        dfs(n, 0, i);
    }
    return answer;
}