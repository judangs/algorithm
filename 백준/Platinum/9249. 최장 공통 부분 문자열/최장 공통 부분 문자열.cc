#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

string A, B;

bool compare_to_group(vector<int> & group, int d, int a, int b) {
    if(group[a] == group[b])
        return group[a + d] < group[b + d];
    return group[a] < group[b];
}

void build_suffix_array(string word, int psize) {
    
    int n = word.size();
    
    vector<int> group(n + 1);
    vector<int> sa;
    group[n] = -1;

    for(int idx=0; idx<n; idx++) {
        group[idx] = word[idx] - 'a';
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

    vector<int> lcp(n, 0);
    vector<int> sentenceSet(n);
    for(int idx=0; idx<n; idx++) {
        if(idx < psize) sentenceSet[idx] = 1;
        else if(idx > psize) sentenceSet[idx] = 2;
        else sentenceSet[idx] = 0;
    }

    int match = 0;
    int maxlen = 0, index;
    for(int i=0; i<n; i++) {
        if(group[i] == 0) continue;

        int j = sa[group[i] - 1];
        if(sentenceSet[i] == 0 || sentenceSet[j] == 0) continue;

        if(sentenceSet[i] != sentenceSet[j]) {
            while(i + match < n && j + match < n && word[i + match] == word[j + match] && (word[i + match] != '|')) {
                match++;
            }

            lcp[group[i]] = match;
            if(maxlen < lcp[group[i]]) {
                maxlen = lcp[group[i]];
                index = i;
            }
            
            if(match > 0) match--;
        }
    }

    cout << maxlen << "\n";
    cout << word.substr(index, maxlen);
    
}

int main() {

    cin >> A >> B;
    build_suffix_array(A + '|' + B, A.size());
}