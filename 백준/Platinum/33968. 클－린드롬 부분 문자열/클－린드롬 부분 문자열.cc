#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <deque>


using namespace std;

static vector<int> manacher_odd_only(const string& s) {
    int n = (int)s.size();
    vector<int> p(n, 0);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(p[l + r - i], r - i);
        while (0 <= i - k - 1 && i + k + 1 < n && s[i - k - 1] == s[i + k + 1]) k++;
        p[i] = k;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
    return p;
}

static string build_U(const string& T) {
    string U;
    U.reserve(2 * (int)T.size() + 1);
    U.push_back('@');
    for (char c : T) {
        U.push_back(c);
        U.push_back('@');
    }
    return U;
}

static vector<int> sliding_min(const vector<int>& a, int k) {
    int n = (int)a.size();
    vector<int> res;
    if (k <= 0 || k > n) return res;
    res.reserve(n - k + 1);

    deque<int> dq;
    for (int i = 0; i < n; i++) {
        while (!dq.empty() && a[dq.back()] >= a[i]) dq.pop_back();
        dq.push_back(i);
        while (!dq.empty() && dq.front() <= i - k) dq.pop_front();
        if (i >= k - 1) res.push_back(a[dq.front()]);
    }
    return res;
}

int main() {

    int N;
    string S;
    cin >> N >> S;

    for (int K = 1; K <= N; K++) {
        vector<int> A_odd(N, 0), A_even(N, 0);

        for (int r = 0; r < K; r++) {
            string T;
            for (int pos = r; pos < N; pos += K) T.push_back(S[pos]);
            int m = (int)T.size();
            if (m == 0) continue;

            string U = build_U(T);
            vector<int> P = manacher_odd_only(U);

            for (int t = 0; t < m; t++) {
                int pos = r + t * K;

                int centerChar = 2 * t + 1;
                A_odd[pos] = P[centerChar] / 2;

                if (t + 1 < m) {
                    int centerSep = 2 * (t + 1);
                    A_even[pos] = P[centerSep] / 2;
                } else {
                    A_even[pos] = 0;
                }
            }
        }

        long long ans = 0;

        {
            auto mins = sliding_min(A_odd, K);
            for (int start = 0; start <= N - K; start++) {
                ans += (long long)mins[start] + 1;
            }
        }

        if (2 * K <= N) {
            auto mins = sliding_min(A_even, K);
            for (int start = 0; start <= N - 2 * K; start++) {
                ans += (long long)mins[start];
            }
        }

        cout << ans << "\n";
    }
}
