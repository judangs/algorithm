#include <string>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

long long solution(int k, int d) {

    long long answer = 0;
    for(int current = 0; current <= d; current += k) {
        answer += ((long long )sqrt(pow(d, 2) - pow(current, 2))) / (long long) k + 1;
    }

    return answer;
}