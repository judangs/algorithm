#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(int n, vector<vector<int>> data) {
    sort(data.begin(), data.end());

    int answer = 0;
    for(int i=0; i<data.size()-1; i++) {
        int current_x = data[i][0];
        int current_y = data[i][1];

        for(int j=i+1; j<data.size(); j++) {
            int next_x = data[j][0];
            int next_y = data[j][1];
            
            if(current_x == next_x || current_y == next_y) continue;

            bool flag = true;
            for(int k=i + 1; k < j; k++) {
                int compare_x = data[k][0];
                int compare_y = data[k][1];
                if(current_x < compare_x && compare_x < next_x) {
                    if(compare_y > min(current_y, next_y) && compare_y < max(current_y, next_y)) {
                        flag = false;
                        break;
                    }
                }
            }

            if(flag == true) answer++;
        }
    }

    return answer;
}