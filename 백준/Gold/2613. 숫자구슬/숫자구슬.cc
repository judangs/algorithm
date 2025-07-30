#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
int bead[301];

int valid(int maxcost) {
    int sum = 0, group = 1;
    for(int i = 1; i <= N; i++) {
        if(sum + bead[i] > maxcost) {
            group++;
            sum = bead[i];
        }
        else {
            sum += bead[i];
        }
    }
    return group;
}

vector<int> tracing(int maxcost) {
    vector<int> groups;
    int sum = 0, count = 0;
    
    for(int i = 1; i <= N; i++) {
        if(sum + bead[i] > maxcost) {
            if(count > 0) groups.push_back(count);
            sum = bead[i];
            count = 1;
        }
        else {
            sum += bead[i];
            count++;
        }
    }
    if(count > 0) groups.push_back(count);
    
    while(groups.size() < M) {
        for(int i = groups.size() - 1; i >= 0; i--) {
            if(groups[i] > 1) {
                groups[i]--;
                groups.insert(groups.begin() + i + 1, 1);
                break;
            }
        }
    }
    
    return groups;
}

int main() {
    cin >> N >> M;
    
    int left = 1;
    for(int i = 1; i <= N; i++) {
        cin >> bead[i];
        left = max(left, bead[i]);
    }
    
    int right = 30000;
    while(left < right) {
        int mid = (left + right) / 2;
        
        if(valid(mid) <= M) {
            right = mid;
        }
        else {
            left = mid + 1;
        }
    }
    
    cout << left << endl;
    
    vector<int> answer = tracing(left);
    for(int i = 0; i < answer.size(); i++) {
        cout << answer[i] << " ";
    }
    cout << endl;
    
}