#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(int n, long long left, long long right) {

    vector<int> answer;
    for(long long current = left; current<=right; current++) {
        long long y = current / n;
        long long x = current % n;

        answer.push_back(max(y, x) + 1);
    }

    return answer;
}