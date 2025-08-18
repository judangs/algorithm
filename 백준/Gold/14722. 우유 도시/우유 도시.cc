#include <iostream>
#include <algorithm>
#include <memory.h>

using namespace std;

int N;
int map[1000][1000];
int cache[4][1000][1000];

int next(int type) {
    return (type + 1 == 4 ? 1 : type + 1);
}

int drinking(int type, int y, int x) {
    if(y == N - 1 && x == N - 1) 
        return (next(type) == map[y][x] ? 1 : 0);
    
    int & ret = cache[type][y][x];
    if(ret != -1) return ret;

    ret = 0;
    if(y + 1 < N) {
        ret = max(ret, drinking(type, y + 1, x));
        if(next(type) == map[y][x]) ret = max(ret, 1 + drinking(map[y][x], y + 1, x));
    }
    if(x + 1 < N) {
        ret = max(ret, drinking(type, y, x + 1));
        if(next(type) == map[y][x]) ret = max(ret, 1 + drinking(map[y][x], y, x + 1));
    }

    return ret;
}

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cin >> map[i][j]; map[i][j]++;
        }
    }

    memset(cache, -1, sizeof(cache));
    
    int answer = drinking(0, 0, 0);
    cout << answer << endl;
    
}