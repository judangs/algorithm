#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

bool compare(vector<int> a, vector<int> b) {
    if(a.front() == b.front())
        return a.back() > b.back();
    return a.front() < b.front();
}

int solution(vector<vector<int>> scores) {
    vector<int> rank;
    
    pair<int, int> pivot = make_pair(scores.front()[0], scores.front()[1]);
    sort(scores.begin(), scores.end(), compare);

    int n = scores.size() - 1;
    int second_max = -1;
    for(int idx=n; idx>=0; idx--) {
        if(pivot.first < scores[idx][0] && pivot.second < scores[idx][1])
            return -1;
        else if(scores[idx][1] >= second_max) {
            second_max = scores[idx][1];
            rank.push_back(scores[idx][0] + scores[idx][1]);
        }
    }

    sort(rank.rbegin(), rank.rend());

    auto iter = find(rank.begin(), rank.end(), (pivot.first + pivot.second));
    if(iter == rank.end())
        return -1;
    return (iter - rank.begin() + 1);
}