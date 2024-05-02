#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

map<int, int> m;

int solution(int k, vector<int> tangerine) {
    for(int t: tangerine) {
        m[t]++;
    }

    vector<int> arr;
    for(auto iter=m.begin(); iter!=m.end(); iter++) {
        arr.push_back(iter->second);
    }

    sort(arr.rbegin(), arr.rend());
    int current = 0, answer = 0;
    while(k > 0) {
        k -= arr[current++];
        answer++;
    }

    return answer;
}