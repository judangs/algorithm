#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> arr;

long long factorial(int n) {
    if(n == 1 || n == 0)
        return 1;
    return n * factorial(n - 1);
}

vector<int> solution(int n, long long k) {
    for(int i=1; i<=n; i++) {
        arr.push_back(i);
    }

    k--;
    vector<int> answer;

    while(n) {
        long long step = factorial(n - 1);
        int idx = k / step;
        answer.push_back(arr[idx]);
        arr.erase(arr.begin() + idx);

        k %= step;
        n--;
    }

    return answer;
}