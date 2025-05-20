#include <iostream>
#include <vector>

using namespace std;

int L;
char A;
vector<char> adv;

int overlap_pre_and_subffix() {
    int n = adv.size();
    
    vector<int> pi(n, 0);

    int begin = 1, match = 0;
    while(begin + match < n) {
        if(adv[begin + match] == adv[match]) {
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

    return pi[n - 1];
}

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> L;
    for(int idx=0; idx<L; idx++) {
        cin >> A;
        adv.push_back(A);
    }

    cout << (L - overlap_pre_and_subffix());
}