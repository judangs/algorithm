#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

int T;
string dna;

ll build_suffix_array_to_lcp(string word) {
    
    ll n = word.size();
    vector<int> group(n + 1, -1);
    vector<int> sa;
    for(int idx=0; idx < n; idx++) {
        group[idx] = word[idx];
        sa.push_back(idx);
    }

    int d = 1;  

    while(d < n) {

        auto compare = [& group, d](int a, int b) {
            if(group[a] == group[b])
                return group[a + d] < group[b + d];
            return group[a] < group[b];
        };            
        
        sort(sa.begin(), sa.end(), compare);

        vector<int> next = group;
        next[sa.front()] = 0;
        for(int idx=1; idx < n; idx++) {
            if(compare(sa[idx - 1], sa[idx]))
                next[sa[idx]] = next[sa[idx - 1]] + 1;
            else 
                next[sa[idx]] = next[sa[idx - 1]];
        }

        group = next;
        d <<= 1;   
    }

    vector<int> lcp(n, 0);

    int match = 0;
    for(int i=0; i<n; i++) {
        if(group[i] == 0) continue;

        int j = sa[group[i] - 1];
        while(i + match < n && j + match < n && word[i + match] == word[j + match]) {
            match++;
        }

        lcp[group[i]] = match;
        if(match > 0) match--;
    }
    
    ll answer = 0ll;
    for(int r=1; r<n; r++) {
        if(lcp[r - 1] < lcp[r])
            answer += (lcp[r] - lcp[r - 1]);
    }

    return answer;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while(T--) {
        cin >> dna;
        cout << build_suffix_array_to_lcp(dna) << "\n";
    }

}