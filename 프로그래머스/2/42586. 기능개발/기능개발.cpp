#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    
    vector<int> days(speeds.size(), 0);
    
    for(int i=0; i<progresses.size(); i++) {
        int remain = (100 - progresses[i]) / speeds[i];
        
        if((100 - progresses[i]) % speeds[i] > 0) remain++;
        if(remain == 0) remain = 1;
        days[i] = remain;
    }
    
    days.push_back(999);
    
    for(int i=0; i<days.size()-1; i++) {
        int count = 1;
        int ptr = i + 1;
        while(days[i] >= days[ptr]) {
            ptr++;
            count++;
        }
        i = ptr - 1;
        
        answer.push_back(count);
    }
    
    return answer;
}