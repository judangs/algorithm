#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <sstream>

using namespace std;

bool compare(string a, string b) {
    return a.size() < b.size();
}

vector<int> solution(string s) {
    vector<int> answer;
    
    while(s.find("},{") != string::npos) {
        s.replace(s.find("},{"), 3, " ");
    }
    
    while(s.find("{") != string::npos) {
        s.replace(s.find("{"), 1, "");
    }
    
    while(s.find("}") != string::npos) {
        s.replace(s.find("}"), 1, "");
    }    
    
    stringstream iss(s);
    string buffer;
    
    vector<string> arr;
    while(getline(iss, buffer, ' ')) {
        arr.push_back(buffer);
    }
    
    sort(arr.begin(), arr.end(), compare);
    set<int> ret;
    
    for(int i=0; i<arr.size(); i++) {
        stringstream iss(arr[i]);
        while(getline(iss, buffer, ',')) {
            if(find(ret.begin(), ret.end(), stoi(buffer)) == ret.end()) {
                answer.push_back(stoi(buffer));
                ret.insert(stoi(buffer));
            }
        }
    }
    
    return answer;
}