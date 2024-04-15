#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int solution(int n, vector<int> stations, int w) {

    int answer = 0;
     if(1 < stations.front() - w) {
        double range = stations.front() - w - 1;
        answer += ceil(range / (2 * w + 1));
     }


    if(stations.size() != 1) {
        for(int i=1; i<stations.size(); i++) {
            int before = stations[i-1];
            int current = stations[i];

            double range = (current - w) - (before + w) - 1;
            answer += ceil(range / (2 * w + 1));
        }
    }

    if(stations.back() + w < n) {
        double range = n - (stations.back() + w);
        answer += ceil(range / (2 * w + 1));
    }

    return answer;
}