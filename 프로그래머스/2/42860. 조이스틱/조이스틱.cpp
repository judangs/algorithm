#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(string name) {
    string current = string(name.size(), 'A');

    int n = name.size();
    int move = n - 1;
    int answer = 0;
    for(int i=0; i<n; i++) {
        answer += min(name[i] - 'A', 'Z' - name[i] + 1);

        int y = i + 1;
        while(y < n && name[y] == 'A') y++;

        // 2x + (n-y) : forward, 2(n-y) + x : backward
        move = min(move, min(2*i + (n-y), 2*(n-y) + i));
    }

    answer += move;
    return answer;
}