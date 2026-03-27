#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

vector<string> parse(string word) {
    
    istringstream iss(word);
    vector<string> ret;
    string buffer = "";
    
    while(getline(iss, buffer, ' ')) {
        if(buffer.size() != 0)
            ret.push_back(buffer);
    }
    
    return ret;
}

int solution(string message, vector<vector<int>> spoiler_ranges) {
    
    int n = message.size();
    
    int idx = 0;
    set<string> w;
    for(auto & spolier: spoiler_ranges) {
        int s = spolier.front(), e = spolier.back();
        while(0 <= s && message[s] != ' ') s--;
        
        if(idx < s) {
            string word = "";
            while(idx < s) 
                word += message[idx++];

            vector<string> words = parse(word);
            for(auto ww: words) {
                w.insert(ww);
            }               
        }     
        
        while(e < n && message[e] != ' ') e++;
        idx = max(idx, e + 1);
    }
    
    int lastp = spoiler_ranges.back()[1];
    while(lastp < n && message[lastp] != ' ') lastp++;
    idx = max(idx, lastp + 1);
    
    string lastw = "";
    for(; idx < n; idx++) lastw += message[idx];
    
    vector<string> lastww = parse(lastw);
    for(auto & ww: lastww) {
        w.insert(ww);
    }
    
    set<string> visit;
    int ans = 0;
    for(auto & spolier: spoiler_ranges) {
        int s = spolier.front(), e = spolier.back();
        string word = "";
        for(int i = s; i <= e; i++) word += message[i];
        
        if(message[s] != ' ') s--;
        if(message[e] != ' ') e++;
        
        while(0 <= s && message[s] != ' ') word = message[s--] + word;
        while(e < n && message[e] != ' ') word += message[e++];
        
        vector<string> words = parse(word);
        for(auto & ww: words) {
            if(w.find(ww) == w.end() && visit.find(ww) == visit.end()) {
                visit.insert(ww);
                ans++;
            }
        }
    }
    
    return ans;
    
}