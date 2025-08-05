#include <iostream>
#include <cstring>
#include <vector>

using namespace std;
typedef long long ll;

string S; int K;

vector<int> build_sparse_table() {

    int begin = 1, match = 0, n = S.size();
    vector<int> pi(n, 0);
    while(begin + match < n) {
        if(S[begin + match] == S[match]) {
            match++;
            pi[begin + match - 1] = match;
        }
        else {
            if(match == 0)
                begin++;
            else {
                begin += (match - pi[match - 1]);
                match = pi[match - 1];
            }
        }
    }

    return pi;

}

int main() {

    cin >> S >> K;
    vector<int> sparse = build_sparse_table();
    ll lcm = sparse.back();

    ll answer = S.size() * K - lcm * (K - 1);
    cout << answer << endl;

}