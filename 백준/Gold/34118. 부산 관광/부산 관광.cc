#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int N;
string A, B;

const int INF = 1e9;
vector<int> price(4);


int dp[2001][6][6][5];

int solve(int day, int remA, int remB, int remP) {
    if (day == N) return 0;

    int &ret = dp[day][remA][remB][remP];
    if (ret != -1) return ret;
    ret = INF;

    bool needA = (A[day] == '1');
    bool needB = (B[day] == '1');

    int lenA[4]  = {0, 1, 3, 5};
    int lenB[4]  = {0, 1, 3, 5};
    int lenP[2]  = {0, 4};

    int costA[4] = {0, price[0], price[1], price[2]};
    int costB[4] = {0, price[0], price[1], price[2]};
    int costP[2] = {0, price[3]};


    for (int ia = 0; ia < 4; ++ia) {
        for (int ib = 0; ib < 4; ++ib) {
            for (int ip = 0; ip < 2; ++ip) {
                int cost = costA[ia] + costB[ib] + costP[ip];

                int nRemA = max(remA, lenA[ia]);
                int nRemB = max(remB, lenB[ib]);
                int nRemP = max(remP, lenP[ip]);

                bool coverA = !needA || (nRemA > 0 || nRemP > 0);
                bool coverB = !needB || (nRemB > 0 || nRemP > 0);
                if (!coverA || !coverB) continue;

                int afterA = (nRemA > 0 ? nRemA - 1 : 0);
                int afterB = (nRemB > 0 ? nRemB - 1 : 0);
                int afterP = (nRemP > 0 ? nRemP - 1 : 0);

                ret = min(ret, cost + solve(day + 1, afterA, afterB, afterP));
            }
        }
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    cin >> A >> B;
    for (int & p : price) cin >> p;

    memset(dp, -1, sizeof(dp));

    int answer = solve(0, 0, 0, 0);
    cout << answer << '\n';

}
