#include <iostream>
#include <memory.h>

using namespace std;

const int mod = 10000;
int N, K;

int choice[101];
int dp[101][4][3];

int make(int day, int food, int cont) {
    if(day == N) return 1;
    if(dp[day][food][cont] != -1) return dp[day][food][cont];

    int & ret = dp[day][food][cont];
    ret = 0;
    
    if(choice[day + 1] != -1) {
        if(food == choice[day + 1]) {
            if(cont + 1 < 3)
                ret = (ret + make(day + 1, choice[day + 1], cont + 1)) % mod;
        }
        else 
            ret = (ret + make(day + 1, choice[day + 1], 1)) % mod;
    }
    else {
        for(int pick=1; pick <= 3; pick++) {
            if(food == pick) {
                if(cont + 1 < 3)
                    ret = (ret + make(day + 1, pick, cont + 1)) % mod;
            }
            else
                ret = (ret + make(day + 1, pick, 1)) % mod;
        }
    }

    ret %= mod;
    return ret;
     
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    memset(choice, -1, sizeof(choice));
    memset(dp, -1, sizeof(dp));

    cin >> N >> K;
    for(int i=0; i<K; i++) {
        int A, B; cin >> A >> B;
        choice[A] = B;
    }

    int answer = make(0, 0, 0);
    cout << answer << endl;

}