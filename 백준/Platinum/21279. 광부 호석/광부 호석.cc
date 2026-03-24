#include <iostream>
#include <vector>

#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define MAXLEN 100000

using namespace std;
typedef long long ll;

int N; ll C;

int main() {

    fastio;

    vector<pair<int, ll>> xgadget[MAXLEN + 1];
    vector<pair<int, ll>> ygadget[MAXLEN + 1];
    
    cin >> N >> C;
    for(int i = 0; i < N; i++) {
        int X, Y; ll V; cin >> X >> Y >> V;
        xgadget[X].push_back({ Y, V }); ygadget[Y].push_back({ X, V });
    }

    int H = MAXLEN, W = -1;
    int count = 0;
    ll ans = 0ll, now = 0ll;
    while(0 <= H && W < MAXLEN) {

        int i;
        if(count < C) {

            W++;

            for(int i = 0; i < xgadget[W].size(); i++) {
                if(xgadget[W][i].first <= H) {
                    now += xgadget[W][i].second;
                    count++;
                }
            }

            if(count <= C)
                ans = max(ans, now);
        }
        else {
            for(int i = 0; i < ygadget[H].size(); i++) {
                if(ygadget[H][i].first <= W) {
                    now -= ygadget[H][i].second;
                    count--;
                }
            }

            H--;
        }
    }

    cout << ans << '\n';
    

}