#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> solution(vector<int> sequence, int k) {

    vector<int> answer;

    int start=0, end = 0;
    int current = 0;
    int max_length = INT32_MAX;
    while(end < sequence.size()) {
        current += sequence[end];
        if(current >= k) {
            while(current > k) {
                current -= sequence[start++];
            }

            if(current == k && (end - start) < max_length) {
                answer = {start, end};
                max_length = (end - start);
            }
        }
        end++;
    }

    return answer;
}