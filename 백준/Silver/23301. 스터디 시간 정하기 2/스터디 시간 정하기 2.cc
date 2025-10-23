#include <iostream>
#include <vector>
#include <set>

#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int N, T;
vector<pair<int, int>> timetables[100000];
vector<int> toidx(100000, 0);

int main() {
    fastio;
    
    cin >> N >> T;
    for(int i = 0; i < N; i++) {
        int k; cin >> k;
        timetables[i].resize(k);
        for(int j = 0; j < k; j++) {
            int s, e; cin >> s >> e;   
            timetables[i][j] = { s, e };
        }
    }

    vector<int> available(100001, 0);

    int satisfied = 0;
    int start = 0, end = start + T;
    
    for(int i = start; i < end; i++) {
        for(int person = 0; person < N; person++) {
            while(toidx[person] < timetables[person].size() && 
                  i >= timetables[person][toidx[person]].second) {
                toidx[person]++;
            }

            if(toidx[person] < timetables[person].size() && 
               timetables[person][toidx[person]].first <= i && 
               i < timetables[person][toidx[person]].second) {
                available[i]++;
                satisfied++;
            }
        }
    }

    int satisfiedmax = satisfied;
    pair<int, int> answer = { start, end };

    while(end <= 100000) {
        int nextsatisfied = satisfied;
        
        nextsatisfied -= available[start]; 
        available[start] = 0;

        start++; end++;

        for(int person = 0; person < N; person++) {
            while(toidx[person] < timetables[person].size() && (end-1) >= timetables[person][toidx[person]].second) {
                toidx[person]++;
            }
            if(toidx[person] < timetables[person].size() && timetables[person][toidx[person]].first <= (end-1) && 
               (end-1) < timetables[person][toidx[person]].second) {
                available[end-1]++;
                nextsatisfied++;
            }
        }

        if(satisfiedmax < nextsatisfied) {
            satisfiedmax = nextsatisfied;
            answer = { start, end };
        }

        satisfied = nextsatisfied;
    }

    cout << answer.first << " " << answer.second << endl;
   
}