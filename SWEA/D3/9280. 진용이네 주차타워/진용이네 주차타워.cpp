#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

int T, N, M;
vector<int> parking;
vector<int> car;
vector<int> where;

int main() {
    cin >> T;
    for(int k=1; k<=T; k++) {
        cin >> N >> M;

        parking.resize(N);
        car.resize(M);
        where.resize(M, -1);
        priority_queue<int, vector<int>, greater<int>> pq;
        
        int cost;
        for(int i=0; i<N; i++) {
            cin >> cost;
            parking[i] = cost;
            pq.push(i);
        }

        int weight;
        for(int i=0; i<M; i++) {
            cin >> weight;
            car[i] = weight;
        }

        queue<int> q;

        int state;
        int total_cost = 0;
        for(int i=0; i<2*M; i++) {
            cin >> state;
            if(state > 0) {
                if(!pq.empty()) {
                    where[state-1] = pq.top();
                    total_cost += car[state-1] * parking[pq.top()];
                    pq.pop();
                }
                else {
                    q.push(state - 1);
                }
            }
            else {
                state = abs(state) - 1;
                if(!q.empty()) {
                    where[q.front()] = where[state];
                    total_cost += car[q.front()] * parking[where[state]];
                    q.pop();
                }
                else {
                    pq.push(where[state]);
                }

                where[state] = -1;
            }
        }
        cout << "#" << k << " " << total_cost << endl;
        
    }
}