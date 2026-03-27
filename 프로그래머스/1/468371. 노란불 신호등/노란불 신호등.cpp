#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> signals) {
    
    int n = signals.size();
    vector<int> tot(n);
    for(int i = 0; i < n; i++) {
        int total = 0;
        for(int j = 0; j < 3; j++) total += signals[i][j];
        tot[i] = total;
    }

    int ans = -1;
    for(int time = 1; time <= 10000000; time++) {
        
        bool is_yellow = true;
        for(int i = 0; i < n; i++) {
            int d = time % tot[i];
            if(!(d != 0 && signals[i].front() < d && d <= signals[i].front() + signals[i][1])) {
                is_yellow = false;
                break;
            }
        }
        
        if(is_yellow) {
            ans = time;
            break;
        }
    }

    return ans;
    
}