#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
vector<int> crane;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;
    for(int i=0; i<N; i++) {
        int w; cin >> w;
        crane.push_back(w);
    }

    cin >> M;
    vector<int> box(M);
    for(int i=0; i<M; i++) cin >> box[i];

    sort(crane.rbegin(), crane.rend());
    sort(box.rbegin(), box.rend());

    if(crane.front() < box.front()) cout << "-1" << endl;
    else {
        
        int timer = 0;
        vector<bool> visit(M, false);
        while(find(visit.begin(), visit.end(), false) != visit.end()) {
            int p = 0;
            for(int idx=0; idx<M && p < N; idx++) {
                if(!visit[idx] && crane[p] >= box[idx]) {
                    visit[idx] = true; p++;
                }
            }

            timer++;
        }

        cout << timer << endl;

    }

}