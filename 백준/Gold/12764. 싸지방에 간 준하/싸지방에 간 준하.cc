#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;

int N;
int seat[100001];
priority_queue<int, vector<int>, greater<int>> open;

struct Usage {
    int start, end, seat;
    
    bool operator>(const Usage & o) const {
        return end > o.end;
    }
};
priority_queue<Usage, vector<Usage>, greater<Usage>> closed;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;
    vector<Usage> com(N);
    for(int i=0; i<N; i++) {
        int p, q; cin >> p >> q;
        com[i] = {p, q, 0};
    }

    sort(com.begin(), com.end(), [](const Usage & l, const Usage & r) {
        return l.start < r.start;
    });

    int count = 0;
    for(auto & [start, end, none]: com) {
        
        while(!closed.empty() && closed.top().end < start) {
            auto exit = closed.top(); closed.pop();
            open.push(exit.seat);
        }
        
        if(open.empty()) {
            count++;
            open.push(count);
        }

        closed.push({0, end, open.top()});
        seat[open.top()]++;
        open.pop();
        
    }

    cout << count << endl;
    for(int i=1; i<=count; i++) cout << seat[i] << " ";
    cout << endl;
    

}