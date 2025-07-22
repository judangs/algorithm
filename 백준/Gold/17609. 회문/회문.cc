#include <iostream>
#include <cstring>

using namespace std;

int T;
string word;

pair<bool, int> is_palindrome(int l, int r, int skip) {
    if(l >= r) return {true, skip};
    if(word[l] == word[r]) return is_palindrome(l + 1, r - 1, skip);
    else {
        if(skip == 1) return {false, 2};
        auto lskip = is_palindrome(l + 1, r, skip + 1), rskip = is_palindrome(l, r - 1, skip + 1);
        if(lskip.first) return lskip;
        if(rskip.first) return rskip;
        return lskip;
    }
    
}

int main() {

    cin >> T;
    while(T--) {

        cin >> word;
        auto answer = is_palindrome(0, word.size() - 1, 0);
        if(answer.first) cout << answer.second << endl;
        else
            cout << answer.second << endl;
    }
    
    
}