
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iostream>

using namespace std;

int find_number(string s, int pos) {
    s = s.substr(pos);
    
    int count = pos;
    while(isdigit(s[count])) {
        count++;
    }

    return stoi(s.substr(0, count));
}

bool compare(pair<int, string> a, pair<int, string> b) {
    transform(a.second.begin(), a.second.end(), a.second.begin(), ::tolower);
    transform(b.second.begin(), b.second.end(), b.second.begin(), ::tolower);

    int current_a = 0, current_b = 0;
    while(isdigit(a.second[current_a]) == false) {
        current_a++;
    }
    while(isdigit(b.second[current_b]) == false) {
        current_b++;
    }

    string a_header = a.second.substr(0, current_a);
    string b_header = b.second.substr(0, current_b);

    if(a_header == b_header) {
        int number_a = find_number(a.second, current_a);
        int number_b = find_number(b.second, current_b);
        if(number_a == number_b)
            return a.first < b.first;
        return number_a < number_b;
    }
    return a_header < b_header;

}

vector<string> solution(vector<string> files) {
    vector<pair<int, string>> q;
    for(int idx=0; idx<files.size(); idx++) {
        q.push_back(make_pair(idx, files[idx]));
    }

    sort(q.begin(), q.end(), compare);
    
    vector<string> answer;
    for(auto current: q) {
        answer.push_back(current.second);
    }

    return answer;
}