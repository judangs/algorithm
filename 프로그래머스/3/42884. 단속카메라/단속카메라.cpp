#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

bool compare(vector<int> a, vector<int> b) {
    return a[1] < b[1];
}

int solution(vector<vector<int>> routes) {
    sort(routes.begin(), routes.end(), compare);

    int current = INT32_MIN;
    int answer = 0;
    for(auto route: routes) {
        if(current < route[0]) {
            answer++;
            current = route[1];
        }
    }

    return answer;
}