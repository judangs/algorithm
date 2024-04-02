#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
map<string, int> m;

vector<int> solution(string msg) {
    vector<int> answer;
    
    int idx = 1;
    for(idx; idx<=26; idx++) {
        string alpha = alphabet.substr(idx-1, 1);
        m[alpha] = idx;
    }
    
    for(int i=0; i<msg.size(); i++) {
        int end = msg.size() - i;
        int start = 1;

        while(start <= end && m.find(msg.substr(i, start)) != m.end()) {
            start++;
        }
        
        auto iter = m.find(msg.substr(i, start - 1));
        answer.push_back(iter->second);

        m[msg.substr(i, start)] = idx++;

        i += (start - 1) - 1;
    }
    return answer;
}