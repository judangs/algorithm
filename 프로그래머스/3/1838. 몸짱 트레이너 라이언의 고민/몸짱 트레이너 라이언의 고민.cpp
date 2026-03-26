#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

int go(int distance, vector<vector<int>> & visit, int n) {
    
    int ret = 0;
    while(true) {
        
        int y, x; bool flag = false; 
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(visit[i][j] == 0) {
                    visit[i][j] = 2; ret++;
                    y = i, x = j;
                    flag = true;
                    break;
                }
            }
            
            if(flag) break;
        }
        
        if(!flag) break;
        if(flag) {
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    if(visit[i][j] == 0 && abs(i - y) + abs(j - x) < distance)
                        visit[i][j] = 1;
                }
            }
        }
    }
    
    return ret;
    
}

int batch(int distance, int n) {
    
    vector<vector<int>> visit;
    
    int count = 0;
    for(int i = 0; i < n; i++) {
        visit = vector<vector<int>>(n, vector<int>(n, 0));
        visit[0][i] = 2;
        for(int y = 0; y < n; y++) {
            for(int x = 0; x < n; x++) {
                if(y == 0 && x == i) continue;
                if(abs(y - 0) + abs(x - i) < distance)
                    visit[y][x] = 1;
            }
        }
        
        count = max(count, 1 + go(distance, visit, n));
    }
    
    return count;
}

int solution(int n, int m, vector<vector<int>> timetable) {
    
    sort(timetable.begin(), timetable.end(), [](vector<int> & l, vector<int> & r) {
        if(l.front() == r.front())
            return l.back() < r.back();
        return l.front() < r.front();
    });
    
    int mx = 0;
    priority_queue<int, vector<int>, greater<int>> pq;
    for(auto & time: timetable) {
        while(!pq.empty() && pq.top() < time.front())
            pq.pop();
        
        pq.push(time.back());
        mx = max(mx, (int) pq.size());
    }

    if(mx <= 1) return 0;
    
    int ans;
    for(int distance = n * n / 2; 0 < distance; distance--) {
        if(mx <= batch(distance, n)) {
            ans = distance;
            break;
        }
    }
    
    return ans;
}