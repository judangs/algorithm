#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int to_time(string pos) {
    int hour = stoi(pos.substr(0, pos.find(':')));
    int seconds = stoi(pos.substr(pos.find(':') + 1));
    return (60 * hour) + seconds;
}

bool is_opening(int time, string start, string end) {
    return (to_time(start) <= time && time <= to_time(end));
}


string to_time_str(int now) {
    string hour = (now / 60 < 10 ? string(1, '0') + to_string(now / 60) : to_string(now / 60));
    string seconds = (now % 60 < 10 ? string(1, '0') + to_string(now % 60) : to_string(now % 60));
    
    return (hour + ":" + seconds);
}

string solution(string video_len, string pos, string op_start, string op_end, vector<string> commands) {
    
    int now = to_time(pos);
    if(is_opening(now, op_start, op_end))
        now = to_time(op_end);
    
    for(auto & command: commands) {
        if(command == "prev") {
            now = max(0, now - 10);
        }
        if(command == "next") {
            now = min(to_time(video_len), now + 10);
        }
        
        if(is_opening(now, op_start, op_end))
            now = to_time(op_end);
    }
    
    return to_time_str(now);
    
}