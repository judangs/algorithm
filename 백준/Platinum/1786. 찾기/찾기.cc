#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

string T, P;
int n, m;
vector<int> pi;
vector<int> answer;

void build_sparse_table() {

    int begin = 1, match = 0;
    while(begin + match < m) {
        if(P[begin + match] == P[match]) {
            match++;
            pi[begin + match - 1] = match;
        }
        else {
            if(match == 0) begin++;
            else {
                begin += (match - pi[match - 1]);
                match = pi[match - 1];
            }
        }
    }
}

void search_word_with_kmp() {

    build_sparse_table();

    int begin = 0, match = 0;
    while(begin <= n - m) {
        if(match < m && T[begin + match] == P[match]) {
            match++;
            if(match == P.size()) {
                answer.push_back(begin + 1);
            }
        }
        else {
            if(match == 0) begin++;
            else {
                begin += (match - pi[match - 1]);
                match = pi[match - 1];
            }
        }
    }
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    getline(cin, T);
    getline(cin, P);

    n = T.size(), m = P.size();

    pi.resize(m, 0);

    search_word_with_kmp();
    cout << answer.size() << "\n";
    for(auto ans: answer) {
        cout << ans << "\n";
    }

}