#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

int parse_log(string log) {
    
    int hour = stoi(log.substr(0, 2)) * 60 * 60;
    int minute = stoi(log.substr(3, 2)) * 60;
    int second = stoi(log.substr(6, 2));
    
    return hour + minute + second;
}

string parse_to_string_time(int time) {
    int hour = time / (60 * 60);
    int minute = (time % (60 * 60)) / 60;
    int second = time % 60;

    string answer = "";
    if(hour < 10)
        answer += "0";
    answer += (to_string(hour) + ":");
    
    if(minute < 10)
        answer += "0";
    answer += (to_string(minute) + ":");

    if(second < 10)
        answer += "0";
    answer += to_string(second);

    return answer;
}

string solution(string play_time, string adv_time, vector<string> logs) {
    vector<int> video(360000, 0);
    
    string buffer;
    for(string log: logs) {
        
        stringstream iss(log);
        getline(iss, buffer, '-');
        int start = parse_log(buffer);
        
        getline(iss, buffer, '-');
        int end = parse_log(buffer);
        
        for(int i=start; i<end; i++) {
            video[i]++;
        }
    }
    
    pair<int, int> current_play = make_pair(0, parse_log(adv_time));
    long long total_play_time = 0;
    for(int i=current_play.first; i<=current_play.second; i++) {
        total_play_time += video[i];
    }
    
    long long max_play_time = total_play_time;
    int max_play_start = current_play.first;
    int end_play = parse_log("99:59:59");
    while(current_play.second <= end_play) {
        total_play_time -= video[current_play.first];
        total_play_time += video[current_play.second];
        
        current_play.first++;
        current_play.second++;
        if(total_play_time > max_play_time) {
            max_play_time = total_play_time;
            max_play_start = current_play.first;
        }
    }
    
    return parse_to_string_time(max_play_start);
}