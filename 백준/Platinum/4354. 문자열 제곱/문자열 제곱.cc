#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

string s;

int overlap_pre_subffix() {

    int n = s.size();
    vector<int> pi(n, 0);
    
    int begin = 1, match = 0;
    while(begin + match < n) {
        if(s[begin + match] == s[match]) {
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

    return pi.back();
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    while(true) {
        cin >> s;
        if(s == ".") break;

        int n = s.size();

        int min_overlap = (n - overlap_pre_subffix());
        if(n % min_overlap != 0) cout << "1\n";
        else
            cout << (n / min_overlap) << "\n";
    }
}