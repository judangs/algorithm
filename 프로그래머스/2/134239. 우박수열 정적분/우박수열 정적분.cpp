#include <string>
#include <vector>

using namespace std;

vector<double> prefix_sum = {0.0};

vector<double> solution(int k, vector<vector<int>> ranges) {

    int current = k;
    while(current != 1) {
        int next;
        if(current % 2 == 0) next = current / 2;
        else next = current * 3 + 1;

        prefix_sum.emplace_back(prefix_sum.back() + static_cast<double>(current + next) / 2);
        current = next;
    }

    vector<double> answer;
    for(int idx=0; idx<ranges.size(); idx++) {
        int start = ranges[idx][0];
        int end = prefix_sum.size() -1 + ranges[idx][1];

        if(start > end) answer.push_back(-1.0);
        else answer.push_back(prefix_sum[end] - prefix_sum[start]);
    }

    return answer;
}