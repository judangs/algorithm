#include <iostream>
#include <vector>

using namespace std;

long long A, B;
vector<long long> dp(55, 0);

//  i == 4,
// d[i - 1] + (x - (10000 - 1))
// d[i - 1] : MSB(i - 1) 일 때, 1의 개수,
// (x - (1000 - 1)): (x - 0111) i번째 bit의 1 개수. (조건식에서는 2^k 개에 해당하는 수)

long long calc(long long x) {
    long long ret = x & 1;
    
    for(int i=54; i>0; i--) {
        if(x & (1LL << i)) {
            ret += dp[i - 1] + (x - (1LL << i) + 1);
            x -= (1LL << i);
        }
    }

    return ret;
}

int main() {
    cin >> A >> B;

    dp.resize(55);

    dp[0] = 1;
    for(int i=1; i<55; i++) {
        dp[i] = 2 * dp[i - 1] + (1LL << i);
    }

    cout << (calc(B) - calc(A - 1));
}