#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(int n, vector<int> cores) {
    int max_time = *max_element(cores.begin(), cores.end());
    int min_time = *min_element(cores.begin(), cores.end());
    
    int right = max_time * (n - cores.size());
    int left = min_time;

    if(n <= cores.size())
        return n;
    
    while(left <= right) {
        int middle = (left + right) / 2;
        
        int curwork = 0, gowork = 0;
        for(int core: cores) {
            curwork += (middle / core) + 1;
            if(middle % core == 0) {
                curwork--;
                gowork++;
            }
        }

        int total_work = curwork + gowork;
        if(curwork >= n) {
            right = middle - 1;
        }
        else if(total_work < n) {
            left = middle + 1;
        }

        else {
            for(int i=0; i<cores.size(); i++) {
                if(middle % cores[i] == 0) {
                    curwork++;
                    if(curwork == n)
                        return i + 1;
                }
            }
        }
    }
}