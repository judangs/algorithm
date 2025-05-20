#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int N;
char menu;
vector<char> target, current;

vector<int> build_partial_match_table() {

    int n = current.size();
    vector<int> pi(current.size(), 0);
    
    int begin = 1, match = 0;
    while(begin + match < n) {
        if(current[begin + match] == current[match]) {
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

int search() {

    int n = target.size(), m = current.size();
    
    vector<int> pi = build_partial_match_table();

    vector<bool> dinner;
    
    int begin = 0, match = 0;
    while(begin <= n - m) {
        if(match < m && target[begin + match] == current[match]) {
            match++;
            if(match == m) {
                dinner.push_back(true);
            }
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

    return dinner.size();
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    
    cin >> N;
    
    target.resize(2 * N);
    for(int idx=0; idx<N; idx++) {
        cin >> target[idx];
        if(idx < N - 1)
            target[idx + N] = target[idx];
    }

    for(int idx=0; idx<N; idx++) {
        cin >> menu;
        current.push_back(menu);
    }

    int answer = search();
    int _gcd = gcd(answer, N);
    
    answer = answer / _gcd, N = N / _gcd;
    if(answer >= N) cout << "1/1";
    else 
        cout << answer << "/" << N;
}