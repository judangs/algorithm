#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int time_to_number(string time) {
    int hour = stoi(time.substr(0, 2));
    int second = stoi(time.substr(3));
    
    return (60 * hour + second);
}

string number_to_time(int time) {
    string ret = "";
    if(time / 60 < 10) ret += "0";
    ret += to_string(time / 60) + ":";
    if(time % 60 < 10) ret += "0";
    ret += to_string(time % 60);

    return ret;
}

string solution(int n, int t, int m, vector<string> timetable) {
    
    sort(timetable.begin(), timetable.end());
    
    int current = time_to_number("09:00");
    int idx = 0;

    string answer;
    for(int bus=1; bus<=n; bus++, current += t) {
        int count = 0;
        for(idx; idx<timetable.size() && count < m; idx++) {
            int next = time_to_number(timetable[idx]);
            if(next <= current) {
                count++;
            }
            else
                break;
        }
        
        if(count == m) answer = number_to_time(time_to_number(timetable[idx - 1]) - 1);
        else answer = number_to_time(current);
    }

    return answer;
}