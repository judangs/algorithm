#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(int n, vector<int> weak, vector<int> dist) {
    sort(dist.begin(), dist.end());
    
    int idx = weak.size();
    weak.resize(2 * n);
    for(int i=idx; i<weak.size(); i++) {
        weak[i] = weak[i - idx] + n;
    }


    int answer = INT32_MAX;
    do {

        for(int left = 0; left < weak.size() - idx; left++) {
            int current = weak[left], right = left + 1, ptr = 0, count = 0;
            while(ptr < dist.size() && current < weak[left + idx]) {
                if(current + dist[ptr] < weak[right]) {
                    current = weak[right++];
                    ptr++;
                    count++;
                }
                else {
                    right++;
                }
            }

            if(current >= weak[left + idx]) {
                answer = min(answer, count);
            }
        }

    }while(next_permutation(dist.begin(), dist.end()));

    if(answer == INT32_MAX) return -1;
    return answer;
}