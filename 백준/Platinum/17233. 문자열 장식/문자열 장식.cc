#include <iostream>
#include <vector>

#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;

const int inf = 1e9;
int N;
struct Word {
    int len;
    string w;
};
vector<Word> words;
vector<vector<int>> finder;

Word S;

vector<int> get_fail(string P) {

    vector<int> ret(P.size(), 0);
    
    int begin = 1, match = 0, m = P.size();
    while(begin + match < m) {
        if(P[begin + match] == P[match]) {
            match++;
            ret[begin + match - 1] = match;
        }
        else {
            if(match == 0) begin++;
            else {
                begin += match - ret[match - 1];
                match = ret[match - 1];
            }
        }
    }
    return ret;
}

vector<int> KMP(string H, string P) {
    vector<int> fail = get_fail(P);
    vector<int> ret;

    int begin = 0, match = 0, n = H.size(), m = P.size();
    while(begin <= n - m) {
        if(match < m && H[begin + match] == P[match]) {
            match++;
            if(match == m) {
                ret.push_back(begin);
            }
        }
        else {
            if(match == 0) begin++;
            else {
                begin += (match - fail[match - 1]);
                match = fail[match - 1];
            }
        }
    }
    return ret;
}

int main() {
    fastio;
    cin >> N;
    words = vector<Word>(N);
    finder = vector<vector<int>>(N);
    
    for(auto & [len, w]: words) cin >> len >> w;
    cin >> S.len >> S.w;

    for(int i = 0; i < N; i++) {
        vector<int> position = KMP(S.w, words[i].w);
        finder[i] = position;
    }

    vector<int> ptr(N, 0);
    int left = 0, right = 0, answer = inf;
    
    while(right <= S.len) {
        bool valid = true;
        
        for(int i = 0; i < N; i++) {
            while(ptr[i] < finder[i].size() && finder[i][ptr[i]] < left) 
                ptr[i]++;
            
            if(ptr[i] == finder[i].size()) {
                valid = false;
                break;
            }
            
            int begin = finder[i][ptr[i]];
            if(begin < left || begin + words[i].len - 1 > right) {
                valid = false;
                break;
            }
        }
        
        if(valid) {
            answer = min(answer, right - left + 1);
            left++;
            if(left > right) right = left;
        } else {
            right++;
        }
    }
    
    cout << answer << endl;
}