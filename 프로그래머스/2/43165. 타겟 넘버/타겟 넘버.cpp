#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<bool> visit;
vector<int> current;
int answer = 0;

void dfs(int depth, int count, int idx, int target, vector<int> & numbers) {
    if(depth == count) {
        int total = 0, ptr = 0;
        for(int i=0; i<numbers.size(); i++) {
            if(find(current.begin(), current.end(), i) != current.end()) {
                total -= numbers[i];
            }
            else {
                total += numbers[i];
            }
        }
        if(total == target)
            answer++;
        return;
    }

    for(int i=idx; i<numbers.size(); i++) {
        if(visit[i] == false) {
            visit[i] =true;
            current.push_back(i);
            dfs(depth + 1, count, i, target, numbers);
            current.pop_back();
            visit[i] = false;
        }
    }
}

int solution(vector<int> numbers, int target) {

    visit.resize(numbers.size(), false);

    for(int i=1; i<=numbers.size(); i++) {
        dfs(0, i, 0, target, numbers);
    }

    return answer;
}