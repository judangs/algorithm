#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

long long solution(int n, vector<int> times) {

    long long start = 0;
    long long end = 1e18;
    
    long long answer;
    while(start <= end) {
        long long middle = (start + end) / 2;
        
        long long pass = 0;
        for(int time: times)
            pass += (middle /(long long) time);
        
        if(pass < n) {
            start = middle + 1;
        }
        else {
            end = middle - 1;
        }
    }

    return start;
}