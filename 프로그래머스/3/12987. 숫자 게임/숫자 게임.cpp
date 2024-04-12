#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <iostream>

using namespace std;

int solution(vector<int> A, vector<int> B) {
    sort(A.begin(), A.end(), greater<int>());
    sort(B.begin(), B.end(), less<int>());
    
    
    int current = 0, answer = 0;
    for(int i=0; i<A.size(); i++) {
        auto iter = upper_bound(B.begin(), B.end(), A[i]);
        if(iter == B.end()) {
            if(A[i] < B[current]) {
                answer++;
                current++;                
            }
        }
        else {
            B.erase(iter);
            answer++;
        }
    }

    return answer;
}