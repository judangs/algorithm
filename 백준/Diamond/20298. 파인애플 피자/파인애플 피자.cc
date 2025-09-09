#include <iostream>
#include <vector>
#include <algorithm>

#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define MAXSZ 100000

using namespace std;

int N, K;
vector<int> pizza, person;

struct SegTree {

    vector<int> arr;
    SegTree() : arr(4 * MAXSZ) { }

    void clear() { fill(arr.begin(), arr.end(), 0); }

    void update(int node, int l, int r, int num, int val) {
        if(num < l || r < num) return;
        if(l == r && l == num) {
            arr[node] += val; return;
        }

        int m = (l + r) / 2;
        update(2 * node, l, m, num, val);
        update(2 * node + 1, m + 1, r, num, val);
        arr[node] = arr[2 * node] + arr[2 * node + 1];
    }

    int query(int node, int l, int r, int s, int e) {
        if(r < s || e < l) return 0;
        if(s <= l && r <= e) return arr[node];
        
        int m = (l + r) / 2;
        return (query(2 * node, l, m, s, e) + query(2 * node + 1, m + 1, r, s, e));
    }

}seg;

struct Node {
    int lo, hi;
    
    Node(): lo(0), hi(0) { }
    Node(int lo, int hi): lo(lo), hi(hi) { }
    Node(SegTree * seg, int now) {
        lo = seg->query(1, 0, MAXSZ, 0, now - 1);
        hi = seg->query(1, 0, MAXSZ, now + 1, MAXSZ);
    }

    bool operator==(const Node & o) const {
        return (lo == o.lo && hi == o.hi);
    }
};


int KMP(vector<int> & H, vector<int> & P) {


    int n = H.size(), m = P.size();
    vector<Node> now(m);
    for(int i = 0; i < m; i++) {
        now[i] = Node(&seg, P[i]);
        seg.update(1, 0, MAXSZ, P[i], 1);
    }

    seg.clear();

    vector<int> fail(m, 0);
    int begin = 1, match = 0;
    while(begin + match < m) {
        if(now[match] == Node(&seg, P[begin + match])) {

            seg.update(1, 0, MAXSZ, P[begin + match], 1);
            match++;
            fail[begin + match - 1] = match;
        }
        else {
            if(match == 0) begin++;
            else {
                int shift = (match - fail[match - 1]);
                for(int i = 0; i < shift; i++) seg.update(1, 0, MAXSZ, P[begin + i], -1);
                
                begin += shift;
                match = fail[match - 1];
            }
        }
    }

    seg.clear();

    int ret = 0;

    begin = 0, match = 0;
    while(begin <= n - m) {
        if(match < m && now[match] == Node(&seg, H[begin + match])) {

            seg.update(1, 0, MAXSZ, H[begin + match], 1);
            match++;
            if(match == m) {
                ret++;
            }
        }
        else {
            if(match == 0) begin++;
            else {
                int shift = match - fail[match - 1];
                for(int i = 0; i < shift; i++) seg.update(1, 0, MAXSZ, H[begin + i], -1);

                begin += shift;
                match = fail[match - 1];      
            }
        }
    }

    return ret;

}

void compress() {

    auto ordering = [&](vector<int> & arr) {
        vector<int> sorted(arr.begin(), arr.end());
        sort(sorted.begin(), sorted.end());
        sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
        for(auto & rank: arr) rank = lower_bound(sorted.begin(), sorted.end(), rank) - sorted.begin() + 1;
    };

    ordering(pizza); ordering(person);

}

int main() {
    
    fastio;
    cin >> N >> K;
    pizza = vector<int> (N); person = vector<int> (K);
    for(auto & topping: pizza) cin >> topping;
    for(auto & age: person) cin >> age;
    for(int i = 0; i < K - 1; i++) 
        pizza.push_back(pizza[i]);

    compress();
    int answer = KMP(pizza, person);
    cout << answer << endl;

}