#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<vector<bool>> visit;

bool check_range(int y, int x) {
    return 0<= y && y < 11 && 0 <= x && x < 11;
}

int solution(string dirs) {
    visit.resize(132, vector<bool>(132, false));

    pair<int, int> current = make_pair(5, 5);
    int answer = 0;
    for(auto & dir: dirs) {
        switch(dir) {
            case 'U':
                if(check_range(current.first - 1, current.second) == true) {
                    int before = current.first * 11 + current.second;
                    int after = (current.first -1) * 11 + current.second;
                    if(visit[before][after] == false) {
                        answer++;
                        visit[after][before] = true;
                        visit[before][after] = true;
                    }
                    current.first -= 1;
                }
                break;
            case 'D':
                if(check_range(current.first + 1, current.second) == true) {
                    int before = current.first * 11 + current.second;
                    int after = (current.first + 1) * 11 + current.second;
                    if(visit[before][after] == false) {
                        answer++;
                        visit[after][before] = true;
                        visit[before][after] = true;
                    }                    
                    current.first += 1;
                }
                break;            
            case 'L':
                if(check_range(current.first, current.second - 1) == true) {
                    int before = current.first * 11 + current.second;
                    int after = current.first * 11 + current.second - 1;
                    if(visit[before][after] == false) {
                        answer++;
                        visit[after][before] = true;
                        visit[before][after] = true;
                    }                    
                    current.second -= 1;
                }
                break;            
            case 'R':
                if(check_range(current.first, current.second + 1) == true) {
                    int before = current.first * 11 + current.second;
                    int after = current.first * 11 + current.second + 1;
                    if(visit[before][after] == false) {
                        answer++;
                        visit[after][before] = true;
                        visit[before][after] = true;
                    }                    
                    current.second += 1;
                }
                break;            
        }
    }
    
    return answer;
}