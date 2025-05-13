#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#define INF 1e9

using namespace std;

int N, W;
int a, b;

struct Pos {
    int y;
    int x;
};

vector<vector<int>> memorize;
vector<pair<int, int>> crime;
vector<int> trace;

int distance(int current, int next, bool fcar) {
    if(fcar && current == 0) return abs(crime[next].first - 1) + abs(crime[next].second - 1);
    if(!fcar && current == 0) return abs(crime[next].first - N) + abs(crime[next].second - N);
    return abs(crime[next].first - crime[current].first) + abs(crime[next].second - crime[current].second);

}

int dp(int a, int b) {

    if(a == W || b == W) return 0;
    if(memorize[a][b] != -1) return memorize[a][b];

    int next = max(a, b) + 1;
    
    return memorize[a][b] = min(dp(next, b) + distance(a, next, true), 
                                    dp(a, next) + distance(b, next, false));
}

void route(int a, int b) {
    if(a == W || b == W) return;
    
    int next = max(a, b) + 1;
    if(memorize[next][b] + distance(a, next, true) < memorize[a][next] + distance(b, next, false)) {
        cout << "1\n";
        route(next, b);
    }
    else {
        cout << "2\n";
        route(a, next);
    }
}

int main() {

    cin >> N >> W;

    crime.resize(W + 1);
    trace.resize(W + 1);
    memorize.resize(W + 1, vector<int>(W + 1, -1));
    for(int idx=1; idx<=W; idx++) {
        cin >> a >> b;
        crime[idx] = {a, b};
    }


    cout << dp(0, 0) << "\n";
    route(0, 0);
    
}