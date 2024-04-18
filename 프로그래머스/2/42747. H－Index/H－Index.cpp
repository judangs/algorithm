#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(vector<int> citations) {

    sort(citations.begin(), citations.end());

    int answer;
    for(int citation=0; citation<=citations.size(); citation++) {
        auto iter = lower_bound(citations.begin(), citations.end(), citation);
        if(citation <= citations.end() - iter) {
            if(citation >= iter - citations.begin()) {
                answer = citation; 
            }
        }
    }

    return answer;
}