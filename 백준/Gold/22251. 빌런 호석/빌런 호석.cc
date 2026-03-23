#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int N, K, P, X;

vector<vector<int>> flip = {
    { 0, 4, 3, 3, 4, 3, 2, 3, 1, 2}, 
    { 0, 0, 5, 3, 2, 5, 6, 1, 5, 4},
    { 0, 0, 0, 2, 5, 4, 3, 4, 2, 3},
    { 0, 0, 0, 0, 3, 2, 3, 2, 2, 1},
    { 0, 0, 0, 0, 0, 3, 4, 3, 3, 2},
    { 0, 0, 0, 0, 0, 0, 1, 4, 2, 1},
    { 0, 0, 0, 0, 0, 0, 0, 5, 1, 2},
    { 0, 0, 0, 0, 0, 0, 0, 0, 4, 3},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};


int dfs(int depth, string now, int count) {
    if(depth == K) {
        if(1 <= count && 1 <= stoi(now) && stoi(now) <= N) return 1;
        return 0;
    }

    int ret = 0;

    for(int num = 0; num < 10; num++) {
        int a = now[depth] - '0', b = num;
        if(a > b) swap(a, b);
        if(count + flip[a][b] <= P) {
            string next = now; next[depth] = num + '0';
            ret += dfs(depth + 1, next, count + flip[a][b]);
        }
    }


    return ret;

}



int main() {

    cin >> N >> K >> P >> X;

    string now = to_string(X);
    if(now.size() < K) now = string(K - now.size(), '0') + now;

    int answer = dfs(0, now, 0);
    cout << answer << endl;


}