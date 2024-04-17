#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> A, vector<int> B) {

    sort(A.rbegin(), A.rend());
    sort(B.begin(), B.end());

    int answer = 0;
    for(int k=0; k<A.size(); k++) {
        answer += (A[k] * B[k]);
    }

    return answer;
}