#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

bool possible(vector<int> & stones, int n, int k) {
    int count = 0;
    for(int i=0; i<stones.size(); i++) {
        if(stones[i] - n < 0) {
            count++;
        }
        else {
            count = 0;
        }

        if(count >= k)
            return false;
    }

    return true;
}

int solution(vector<int> stones, int k) {
    int start = 0;
    int end = 1e9;
    int answer = 0;
    
    while(start + 1 < end) {
        int mid = (start + end) / 2;
        if(possible(stones, mid, k)) {
            start = mid;
            answer = max(answer, start);
        }
        else {
            end = mid;
        }
    }

    return answer;
}