#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

string S;
vector<int> sa;
vector<int> lcp;

bool compare_to_group(vector<int> & group, int d, int a, int b) {
    if(group[a] == group[b])
        return group[a + d] < group[b + d];
    return group[a] < group[b];
}

vector<int> build_suffix_array() {

    int n = S.size();
    vector<int> group(n + 1);
    group[n] = -1;

    for(int idx=0; idx<n; idx++) {
        group[idx] = S[idx] - 'A';
        sa.push_back(idx);
    }

    int d = 1;
    while(d < n) {
        
        sort(sa.begin(), sa.end(), [& group, d](int a, int b) {
            return compare_to_group(group, d, a, b);
        });

        vector<int> next = group;
        next[sa.front()] = 0;

        for(int idx=1; idx < n; idx++) {
            if(compare_to_group(group, d, sa[idx - 1], sa[idx]))
                next[sa[idx]] = next[sa[idx - 1]] + 1;
            else
                next[sa[idx]] = next[sa[idx - 1]];
        }

        group = next;
        d <<= 1;
    }

    return group;
}

void build_suffix_lcp_array(vector<int> & group) {

    int n = S.size();
    lcp.resize(n, 0);

    int match = 0;
    for(int i=0; i < n; i++) {
        if(group[i] == 0) {
            lcp[group[i]] = 0;
            continue;
        }

        int j = sa[group[i] - 1];
        
        while(i + match < n && j + match < n && S[i + match] == S[j + match])
            match++;

        lcp[group[i]] = match;
        
        if(match > 0) match--;
    }
}

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> S;

    vector<int> group = build_suffix_array();
    build_suffix_lcp_array(group);

    for(auto idx: sa) {
        cout << (idx + 1) << " ";
    }
    cout << "\n";

    cout << "x ";
    for(int i=1; i < S.size(); i++) {
        cout << lcp[i] << " ";
    }

}