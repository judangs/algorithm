#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<vector<int>> answer;

void hannoi(int n, int from, int to, int ref) {
    if(n == 1) {
        answer.push_back({from, to});
        return;
    }

    hannoi(n - 1, from, ref, to);
    answer.push_back({from, to});
    hannoi(n -1, ref, to, from);
}

vector<vector<int>> solution(int n) {
    hannoi(n, 1, 3, 2);
    return answer;
}