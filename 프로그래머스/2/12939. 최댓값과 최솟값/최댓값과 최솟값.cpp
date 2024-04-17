#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>

using namespace std;

string solution(string s) {
    stringstream iss(s);
    string buffer;

    int max_value = INT32_MIN;
    int min_value = INT32_MAX;
    while(getline(iss, buffer, ' ')) {
        max_value = max(max_value, stoi(buffer));
        min_value = min(min_value, stoi(buffer));
    }

    string answer = to_string(min_value) + " " + to_string(max_value);
    return answer;
}