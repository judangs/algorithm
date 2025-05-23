#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

string S;

bool compare_to_group(vector<int> & group, int d, int a, int b) {
    if(group[a] == group[b])
        return group[a + d] < group[b + d];
    return group[a] < group[b];
}

ll build_suffix_array() {
    
    ll n = S.size();
    vector<int> group(n + 1, -1);
    vector<int> sa;
    
    for(int idx=0; idx<n; idx++) {
        group[idx] = S[idx] - 'a';
        sa.push_back(idx);
    }

    int d = 1;
    while(d < n) {
        
        sort(sa.begin(), sa.end(), [& group, d](int a, int b) {
            return compare_to_group(group, d, a, b);
        });

        vector<int> nextGroup = group;
        nextGroup[sa.front()] = 0;
        for(int idx=1; idx<n; idx++) {
            if(compare_to_group(group, d, sa[idx - 1], sa[idx]))
                nextGroup[sa[idx]] = nextGroup[sa[idx - 1]] + 1;
            else 
                nextGroup[sa[idx]] = nextGroup[sa[idx - 1]];
        }

        group = nextGroup;
        d <<= 1;
    }

    vector<ll> lcp(n, 0);

    int match = 0;
    for(int i=0; i<n; i++) {
        if(group[i] == 0) continue;
        
        int j = sa[group[i] - 1];
        while(i + match < n && j + match < n && S[i + match] == S[j + match]) {
            match++;
        }

        lcp[group[i]] = match;

        if(match > 0) match--;
    }

    ll answer = (n * (n + 1)) / 2;
    for(int rank=1; rank<n; rank++) answer -= lcp[rank];

    return answer;
}

int main() {

    cin >> S;
    cout << build_suffix_array();

}