#include <iostream>
#include <vector>
#include <algorithm>

#define MAXJOB 100001

using namespace std;
typedef long long ll;

int N;
struct Job {
    int idx;
    ll time;
};

struct SegTree {
    vector<int> arr;
    
    SegTree(int sz) {
        arr.resize(4 * sz, 0);
    }
    
    void update(int node, int l, int r, int idx, int val) {
        if(idx < l || r < idx) return;
        if(l == r && l == idx) {
            arr[node] = val;
            return;
        }

        int m = (l + r) / 2;
        update(2 * node, l, m, idx, val);
        update(2 * node + 1, m + 1, r, idx, val);
        arr[node] = arr[2 * node] + arr[2 * node + 1];
    }

    ll query(int node, int l, int r, int s, int e) {
        
        if(r < s || e < l) return 0;
        if(s <= l && r <= e) return arr[node];
        
        int m = (l + r) / 2;
        return query(2 * node, l, m, s, e) + query(2 * node + 1, m + 1, r, s, e);
    }
};

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;
    SegTree seg(N);
    vector<Job> jobs(N);

    for(int i=0; i<N; i++) {
        ll t; cin >> t;
        seg.update(1, 0, N - 1, i, 1);
        jobs[i] = {i, t};
    }

    sort(jobs.begin(), jobs.end(), [](Job & l, Job & r) {
        if(l.time == r.time)
            return l.idx < r.idx;
        return l.time < r.time;
    });
    
    vector<ll> answer(N);

    ll time = 0;
    for(auto job: jobs) {
        ll complete = job.time * seg.query(1, 0, N - 1, 0, job.idx) + 
            (job.time - 1ll) * seg.query(1, 0, N - 1, job.idx + 1, N - 1)
                + time;

        seg.update(1, 0, N - 1, job.idx, 0);

        answer[job.idx] = complete;
        time += job.time;
    }

    for(auto t: answer) cout << t << "\n";

}