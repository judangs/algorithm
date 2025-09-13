#include <iostream>
#include <vector>
#include <queue>
#include <functional>

#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;
typedef pair<int, int> pii;

int A, B, N;

struct Gift {
    int time;
    int count;
};
vector<Gift> blue, red;

struct Node {
    int end;
    int seq;

    bool operator>(const Node & o) const {
        return end > o.end;
    }

};


priority_queue<Node, vector<Node>, greater<Node>> pq[2];


int main() {

    fastio;
    cin >> A >> B >> N;
    
    for(int i = 0; i < N; i++) {
        int t, m; char c;
        cin >> t >> c >> m;
        if(c == 'B') blue.push_back(Gift{ t, m });
        if(c == 'R') red.push_back(Gift{ t, m });
    }

    vector<Node> boy, girl;
    for(int timer = 0, ridx = 0, bidx = 0, seq = 1; (bidx < blue.size() || ridx < red.size()); timer++) {

        while(!pq[0].empty() && pq[0].top().end == timer) {
            boy.push_back(pq[0].top()); pq[0].pop();
        }
        while(!pq[1].empty() && pq[1].top().end == timer) {
            girl.push_back(pq[1].top()); pq[1].pop();
        }

        if(bidx < blue.size() && blue[bidx].time <= timer) {
            if(0 < blue[bidx].count && pq[0].empty()) {
                if(A == 0) {
                    for(int i = 0; i < blue[bidx].count; i++)
                        boy.push_back(Node{ timer + A, seq++ });

                    blue[bidx].count = 0;
                }
                else {
                    pq[0].push(Node{ timer + A, seq++});
                    blue[bidx].count -= 1;
                }

                if(blue[bidx].count == 0) bidx++;
            }
        }
        if(ridx < red.size() &&  red[ridx].time <= timer) {
            if(0 < red[ridx].count && pq[1].empty()) {
                if(B == 0) {
                    for(int i = 0; i < red[ridx].count; i++) 
                        girl.push_back(Node{ timer + B, seq++ });
                    red[ridx].count = 0;
                }
                else {
                    pq[1].push(Node{ timer + B, seq++ });
                    red[ridx].count -= 1;
                }

                if(red[ridx].count == 0) ridx++;
            }
        }
    }

    while(!pq[0].empty()) {
        boy.push_back(pq[0].top()); pq[0].pop();
    }
    while(!pq[1].empty()) {
        girl.push_back(pq[1].top()); pq[1].pop();
    }

    cout << boy.size() << '\n';
    for(auto ans: boy) cout << ans.seq << ' ';
    cout << '\n';
    cout << girl.size() << '\n';
    for(auto ans: girl) cout << ans.seq << ' ';
    cout << '\n';
    

}