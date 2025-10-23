#include <iostream>
#include <vector>
#include <deque>

#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int N, Q, C;
vector<int> page(2001);

struct Cache {
    int sz;
    deque<int> dq;

    void compress() {
        deque<int> state;
        int prev = -1, nsz = 0;
        for(int pg : dq) {
            if(pg != prev) {
                state.push_back(pg);
                prev = pg;
                nsz += page[pg];
            }
        }
        dq = state, sz = nsz;
    }

    void push_back(int pg, int psz) {
        sz += psz;
        dq.push_back(pg);
    }
    
    void push_front(int pg, int psz) {
        sz += psz;
        dq.push_front(pg);
    }

    void pop_back() {
        sz -= page[dq.back()];
        dq.pop_back();
    }

    void pop_front() {
        sz -= page[dq.front()];
        dq.pop_front();
    }

    int clear() {
        int ret = sz;
        dq.clear();
        sz = 0;
        return ret;
    }
};

struct PageCache {
    Cache front, back;

    int getTotalSize(int currentPage) {
        return front.sz + back.sz + page[currentPage];
    }

    void compress() {
        back.compress();
    }

    void lru() {
        back.pop_front();
    }

    void cached_back(int now) {
        back.push_back(now, page[now]);
    }

    void front_erase_all() {
        front.clear();
    }

    int go_front(int now) {
        back.push_back(now, page[now]);
        int pg = front.dq.front();
        front.pop_front();
        return pg;
    }

    int go_back(int now) {
        front.push_front(now, page[now]);
        int pg = back.dq.back();
        back.pop_back();
        return pg;
    }
};

PageCache pc;

int main() {
    fastio;
    cin >> N >> Q >> C;
    for(int i = 1; i <= N; i++) {
        cin >> page[i];
    }

    int now = 0;
    while(Q--) {
        char op; cin >> op;
        if(op == 'B') {
            if(pc.back.dq.empty()) continue;
            now = pc.go_back(now);
        }
        else if(op == 'F') {
            if(pc.front.dq.empty()) continue;
            now = pc.go_front(now);
        }
        else if(op == 'A') {
            int pg; cin >> pg;
            if(now == 0) {
                now = pg;
            }
            else {
                pc.front_erase_all();
                pc.cached_back(now);
                now = pg;
                while(pc.getTotalSize(now) > C) {
                    pc.lru();
                }
            }
        }
        else if(op == 'C') {
            pc.compress();
        }
    }

    cout << now << '\n';
    if(pc.back.dq.empty()) {
        cout << -1 << '\n';
    }
    else {
        while(!pc.back.dq.empty()) {
            cout << pc.back.dq.back() << ' ';
            pc.back.dq.pop_back();
        }
        cout << '\n';
    }
    if(pc.front.dq.empty()) {
        cout << -1 << '\n';
    }
    else {
        while(!pc.front.dq.empty()) {
            cout << pc.front.dq.front() << ' ';
            pc.front.dq.pop_front();
        }
        cout << '\n';
    }
}