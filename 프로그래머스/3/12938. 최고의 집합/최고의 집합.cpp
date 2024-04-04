#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;

vector<int> solution(int n, int s) {
    
    if(s / n == 0) {
        return vector<int>(1, -1);
    }
    vector<int> answer(n, s/n);
    
    int mod = s % n;
    for(int i=0; i<mod; i++) {
        answer[i]++;
    }

    sort(answer.begin(), answer.end(), less<int>());
    return answer;
}