#include <iostream>
#include <vector>
#include <cstring>
#include <set>
#include <memory.h>

using namespace std;

const int INF = 1e9;
int N;
string word;
set<string> words;
int overlap[12][12];

struct Node {
    int len;
    string word;

    Node(int _len, string _word): len(_len), word(_word) { }

    bool operator<(const Node & o) const {
        if(len == o.len)
            return word < o.word;
        return len < o.len;
    }
};

vector<vector<Node>> dp;

void count_overlap_char(int l, int r, vector<string> & arr) {

    int n = arr[l].size(), m = arr[r].size();
    int count = 0;
    for(int len=1; len<=min(n, m); len++) {
        if(arr[l].substr(n - len) == arr[r].substr(0, len))
            count = len;
    }

    overlap[l][r] = count;
}

int main() {

    cin >> N;
    for(int i=0; i<N; i++) {
        cin >> word;
        words.insert(word);
    }

    memset(overlap, 0, sizeof(overlap));

    vector<string> unique(words.begin(), words.end());
    N = unique.size();
    vector<bool> included(N, false);
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            if(i == j) continue;
            if(unique[i].find(unique[j]) != string::npos) {
                included[j] = true;
            }
        }
    }

    vector<string> newword;
    for(int i=0; i<N; i++) {
        if(!included[i])
            newword.push_back(unique[i]);
    }

    N = newword.size();
    dp.resize((1 << N), vector<Node>(N, {INF, ""}));
    for(int i=0; i<N; i++) {
        dp[(1 << i)][i] = {static_cast<int>(newword[i].size()), newword[i]};    
    }    

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            if(i == j) continue;
            count_overlap_char(i, j, newword);
        }
    }    

    for(int state=0; state<(1 << N); state++) {
        for(int last=0; last<N; last++) {
            if((state & (1 << last)) == 0) continue;

            for(int next=0; next<N; next++) {
                if((state & (1 << next)) != 0) continue;

                int nstate = state | (1 << next);
                int nextlen = dp[state][last].len + newword[next].size() - overlap[last][next];
                string nextstr = dp[state][last].word + newword[next].substr(overlap[last][next]);
                
                if(nextlen < dp[nstate][next].len || (nextlen == dp[nstate][next].len && nextstr < dp[nstate][next].word)) {
                    dp[nstate][next] = {nextlen, nextstr};
                }
            }
        }
    }
    
    Node answer = {INF, ""};
    for(int i=0; i<N; i++) {
        if(dp[(1 << N) - 1][i] < answer)
            answer = dp[(1 << N) - 1][i];
    }

    cout << answer.word;
}