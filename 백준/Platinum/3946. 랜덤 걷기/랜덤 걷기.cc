#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {

    int P; cin >> P;
    while(P--) {

        int n; double L, R; cin >> n >> L >> R;
        vector<vector<double>> dp(1001, vector<double>(1001));

        for(int start=0; start<=n; start++)
            dp[0][start] = (double) start;

        for(int i=1; i<=n; i++) {
            for(int j=0; j<=n; j++) {
                dp[i][j] = L * (dp[i - 1][j + 1] - 1) + R * (dp[i - 1][max(0, j - 1)] + 1) + (1 - R - L) * dp[i - 1][j];
            }
        }

        double answer = dp[n][0];
        cout << fixed << setprecision(4);
        cout << answer << endl;
    }

}