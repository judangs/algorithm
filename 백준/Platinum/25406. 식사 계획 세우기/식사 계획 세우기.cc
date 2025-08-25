#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <functional>

#define MAXFOOD 300000

using namespace std;

int N;
vector<priority_queue<int, vector<int>, greater<int>>> pq(MAXFOOD + 1);
set<pair<int, int>> counter;
set<pair<int, int>> ordering;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;
    vector<int> food(N + 1);
    for(int idx=1; idx<=N; idx++) {
        cin >> food[idx];
        pq[food[idx]].push(idx);
    }

    for(int type=1; type<=N; type++)
        if(!pq[type].empty()) {
            counter.insert({pq[type].size(), type});
            ordering.insert({pq[type].top(), type});
        }

    int maxcount = counter.rbegin()->first;
    if((N + 1) / 2 < maxcount) {
        cout << "-1" << endl;
        return 0;
    }
    else {

        vector<int> answer(N + 1, 0);
        for(int i=1; i<=N; i++) {
            int remain = (N - i + 1) / 2;
            if(remain < counter.rbegin()->first) {
                                
                auto [ctx, type] = *counter.rbegin();
                
                answer[i] = pq[type].top(); pq[type].pop();
                
                counter.erase({ctx, type});
                ordering.erase({answer[i], type});
                
                if(!pq[type].empty()) {
                    counter.insert({pq[type].size(), type});
                    ordering.insert({pq[type].top(), type});
                }
            }
            else {
                
                for(auto iter=ordering.begin(); iter != ordering.end(); iter++) {
                    if(food[iter->first] != food[answer[i - 1]]) {
                        auto [idx, type] = *iter;

                        answer[i] = idx;
                        
                        counter.erase({pq[type].size(), type});
                        ordering.erase({idx, type});
                        pq[type].pop();

                        if(!pq[type].empty()) {
                            counter.insert({pq[type].size(), type});
                            ordering.insert({pq[type].top(), type});    
                        }

                        break;                        
                    }
                }

            }
        }

        answer.erase(answer.begin());
        for(auto ans: answer) cout << ans << " ";
        cout << endl;

    }

}