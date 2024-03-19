#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

map<string, int> m;

string solution(vector<string> survey, vector<int> choices) {
    string answer = "";
    
    for(int i=0; i<choices.size(); i++) {
        int score = choices[i] - 4;
        string first = string(1, survey[i][0]);
        string second = string(1, survey[i][1]);
        if(score == 0) continue;
        else if(score < 0) {
            m[first] += -score;
        }
        else {
            m[second]+= score;
        }
    }
    
    vector<string> MBTI = {"RT", "CF", "JM", "AN"};
    for(int i=0; i<MBTI.size(); i++) {
        string first = string(1, MBTI[i][0]);
        string second = string(1, MBTI[i][1]);
        
        cout << m[first] << "/ " << m[second] << endl;

        if(m[first] == m[second]) {
            if(first < second) answer += first;
            else answer += second;
        }
        else if(m[first] > m[second]) answer += first;
        else answer += second;
    
    }
    return answer;
}