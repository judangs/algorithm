#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> d;

int check(int distance) {
    int current = 0, remove = 0;
    for(int idx=0; idx<d.size(); idx++) {
        current += d[idx];
        if(current < distance) {
            remove++;
        }
        else {
            current = 0;
        }
    }
    
    return remove;
}


int solution(int distance, vector<int> rocks, int n) {
    
    sort(rocks.begin(), rocks.end());
    
    d.push_back(rocks.front());
    for(int idx=1; idx<rocks.size(); idx++) {
        d.push_back(rocks[idx] - rocks[idx - 1]);
    }
    
    d.push_back(distance - rocks.back());
    
    int left = 1;
    int right = distance + 1;
    
    while(left + 1 < right) {
        int middle = (left + right) / 2;
        if(check(middle) <= n) left = middle;
        else right = middle;
    }
    
    return left;
}