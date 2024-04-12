#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

int time_to_playtime(string start, string end) {
    int s_hour = stoi(start.substr(0, 2));
    int s_min = stoi(start.substr(3, 2));

    int e_hour = stoi(end.substr(0, 2));
    int e_min = stoi(end.substr(3, 2));

    return (60 * e_hour + e_min) - (60 * s_hour + s_min) + 1;
}

string change_melody(string melody, map<string, string> & convert) {
    string ret;
    for(int i=0; i<melody.size(); i++) {
        if(melody[i + 1] == '#') {
            ret += convert[melody.substr(i, 2)];
        }
        else
            ret += melody[i];
    }

    return ret;
}

string solution(string m, vector<string> musicinfos) {


    map<string, string> convert;
    convert["C#"] = "Q";
    convert["D#"] = "W";
    convert["F#"] = "P";
    convert["G#"] = "R";
    convert["A#"] = "T";

    m = change_melody(m, convert);

    string answer;    
    int max_playtime = 0;
    for(string musicinfo: musicinfos) {
        vector<string> info;
        int idx;
        while((idx = musicinfo.find(',')) != string::npos) {
            info.push_back(musicinfo.substr(0, idx));
            musicinfo = musicinfo.substr(idx + 1);
        }
        info.push_back(musicinfo);

        int playtime = time_to_playtime(info[0], info[1]);
        string melody = change_melody(info.back(), convert);

        while(melody.size() < m.size() * 10) {
            melody += melody;
        }
        
        if((idx = melody.find(m)) != string::npos) {
            if(idx < playtime && playtime > max_playtime) {
                answer = info[2];
                max_playtime = playtime;
            }
        }
    }
    
    if(answer.empty())
        return "(None)";
    return
        answer;
}