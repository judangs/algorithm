#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(vector<int> cookie) {
    
    int answer = 0;
    
    for(int pivot=1; pivot<cookie.size(); pivot++) {
        
        int right = pivot - 1, left = right + 1;
        int first = 0, second = 0;
        
        while(true) {
            if(left < 0 || right >= cookie.size()) break;
            
            if(first < second) {
                first += cookie[--left];
            }
            else {
                second += cookie[++right];
            }
            
            if(first == second)
                answer = max(answer, first);            
        }
    }
    return answer;
}