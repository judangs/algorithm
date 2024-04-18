#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> group;

bool compare(vector<int> a, vector<int> b) {
    return a[2] < b[2];
}

int find(int start) {
    if(group[start] == start)
        return start;
    return find(group[start]);
}

void union_find(int a, int b) {
    a = find(a);
    b = find(b);
    
    if(a != b) {
        if(a < b) {
            group[b] = a;
        }
        else {
            group[a] = b;
        }
    }
}

int solution(int n, vector<vector<int>> costs) {

    sort(costs.begin(), costs.end(), compare);
    group.resize(n+1, 0);
    for(int i=1; i<=n; i++) {
        group[i] = i;
    }

    int answer = 0, select = 0;
    for(auto cost: costs) {
        if(select == n -1)
            break;
        
        int start = cost[0];
        int end = cost[1];

        if(find(start) != find(end)) {
            union_find(start, end);
            answer += cost[2];
            select++;
        }
    }

    return answer;
}