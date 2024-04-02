#include <string>
#include <map>
#include <algorithm>
#include <iostream>
#include <cctype>

using namespace std;

map<string, pair<int, int>> m;

int solution(string str1, string str2) {
    
    transform(str1.begin(), str1.end(), str1.begin(), ::toupper);
    transform(str2.begin(), str2.end(), str2.begin(), ::toupper);
    
    for(int i=0; i<str1.size()-1; i++) {
        if(isalpha(str1[i]) && isalpha(str1[i + 1])) {
            m[str1.substr(i, 2)].first++;
        }
    }
    for(int i=0; i<str2.size()-1; i++) {
        if(isalpha(str2[i]) && isalpha(str2[i + 1])) {
            m[str2.substr(i, 2)].second++;
        }
    }
    
    double select_count = 0, union_count = 0;
    for(auto iter=m.begin(); iter!=m.end(); iter++) {
        if(iter->second.first != 0 && iter->second.second != 0) {
            select_count += min(iter->second.first, iter->second.second);
        }
        union_count += max(iter->second.first, iter->second.second);
    }
    
    
    if(union_count == 0 && select_count == 0) return 65536;
    return (int)((select_count / union_count) * 65536);
}