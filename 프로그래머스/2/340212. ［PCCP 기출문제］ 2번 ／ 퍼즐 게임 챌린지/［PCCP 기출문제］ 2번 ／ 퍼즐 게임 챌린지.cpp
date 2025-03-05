#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

bool solve_puzzle(vector<int> & diffs, vector<int> & times, int level, long long limit) {
    
    long long current = 0;
    for(int idx=1; idx<diffs.size(); idx++) {
        if(diffs[idx] <= level) {
            current += times[idx];
        }
        else {
            int retry = diffs[idx] - level;
            current += (times[idx - 1] + times[idx]) * retry + times[idx];
        }
    }
    
    return (current + times.front()) <= limit;
}

int binary_search(vector<int> & diffs, vector<int> & times, int left, int right, long long limit) {
    if(left + 1 >= right) {
        if(solve_puzzle(diffs, times, left, limit) == true) {
            return left;
        }
        return right;
    }
    
    int level = (left + right) / 2;
    if(solve_puzzle(diffs, times, level, limit) == true) {
        return binary_search(diffs, times, left, level, limit);
    }
    else {
        return binary_search(diffs, times, level + 1, right, limit);
    }
}


int solution(vector<int> diffs, vector<int> times, long long limit) {
    
    int max_level = *max_element(diffs.begin(), diffs.end());
    int min_level = *min_element(diffs.begin(), diffs.end());
    
    return binary_search(diffs, times, min_level, max_level, limit);
}