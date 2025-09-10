#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

using namespace std;

const int inf = 1e9;
int n, m;
vector<int> build, pattern;

struct Rank {
    int lo, hi;
};


bool matcher(vector<int> & arr, int begin, int match, int lo, int hi) {
    if(lo != inf && arr[begin + lo] > arr[begin + match]) return false;
    if(hi != inf && arr[begin + hi] < arr[begin + match]) return false;
    return true;
}


vector<int> KMP(vector<int> & H, vector<int> & P) {

    vector<int> nxt(n), prev(n), toidx(n);

    for(int i = 0; i < n; i++) {
        nxt[i] = i + 1;
        prev[i] = i - 1;
        toidx[P[i]] = i;
    }

    vector<Rank> meta(n, { inf, inf });
    for(int i = n - 1, rank; 0 <= i; i--) {

        rank = P[i];

        if(prev[rank] != -1) meta[i].lo = toidx[prev[rank]];
        if(nxt[rank] != n) meta[i].hi = toidx[nxt[rank]];
        
        if(prev[rank] != -1) nxt[prev[rank]] = nxt[rank];
        if(nxt[rank] != n) prev[nxt[rank]] = prev[rank];
    }

    vector<int> fail(n, 0);

    int begin = 1, match = 0;
    while(begin + match < n) {
        if(matcher(P, begin, match, meta[match].lo, meta[match].hi)) {
            match++;
            fail[begin + match - 1] = match;
        }
        else {
            if(match == 0) begin++;
            else {
                begin += (match - fail[match - 1]);
                match = fail[match - 1];
            }
        }
    }
    
    vector<int> ret;

    begin = 0, match = 0;
    while(begin <= m - n) {
        if(match < n && matcher(H, begin, match, meta[match].lo, meta[match].hi)) {
            match++;
            if(match == n) {
                ret.push_back(begin + 1);
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
    cin >> n >> m;
    
    pattern = vector<int> (n);
    build = vector<int> (m);

    for(int i=0; i<n; i++) {
        int s; cin >> s;
        pattern[s - 1] = i;
    }
    for(auto & h: build) cin >> h;

    auto answer = KMP(build, pattern);

    cout << answer.size() << endl;
    for(auto ans: answer)
        cout << ans << " ";
    cout << endl;

}