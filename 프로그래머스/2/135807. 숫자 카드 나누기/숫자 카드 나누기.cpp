#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<vector<int>> dp;

int gcd(int value, int mod) {
    if(mod == 0)
        return value;
    return gcd(mod, value % mod);
}

int solution(vector<int> arrayA, vector<int> arrayB) {

    int gcf_A = arrayA.front();
    for(int i=1; i<arrayA.size(); i++) {
        gcf_A = gcd(gcf_A, arrayA[i]);
    }

    int answer = 0;
    if(gcf_A != 1) {
        int current = 0;
        for(current; current<arrayB.size(); current++) {
            if(arrayB[current] % gcf_A == 0)
                break;
        }
        if(current == arrayB.size()) {
            answer = max(answer, gcf_A);
        }
    }

    int gcf_B = arrayB.front();
    for(int i=1; i<arrayB.size(); i++) {
        gcf_B = gcd(gcf_B, arrayB[i]);
    }

    if(gcf_B != 1) {
        int current = 0;
        for(current; current<arrayA.size(); current++) {
            if(arrayA[current] % gcf_B == 0)
                break;
        }
        if(current == arrayA.size()) {
            answer = max(answer, gcf_B);
        }        
    }
    return answer;
}