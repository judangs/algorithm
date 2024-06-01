#include <iostream>

using namespace std;

long long solution(int w,int h) {

    long long copy_w = w;
    long long copy_h = h;

    long long answer = 0;
    for(long long current = 1; current < w; current++) {
        long long current_height = ((-1 * copy_h * current) + copy_h * copy_w) / copy_w;
        answer += current_height;
    }

    answer *= 2;
    return answer;
}