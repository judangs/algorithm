#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <algorithm>

using namespace std;

int solution(vector<int> cards) {
    vector<bool> visit(cards.size(), false);
    vector<int> group;

    for(int i=0; i<cards.size(); i++) {
        int count = 0, current = i;
        while(!visit[current]) {
            visit[current] = true;
            current = cards[current] - 1;
            count++;
        }
        group.push_back(count);    
    }

    sort(group.begin(), group.end(), greater<int>());
    if(group.size() == 1)
        return 0;
    return group[0] * group[1];
}