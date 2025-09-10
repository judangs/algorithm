#include <iostream>
#include <vector>
#include <algorithm>

#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;

const int inf = 1e9;
int n, m;
vector<int> chart, pattern;

struct Order {
    int lo, hi, same;
};
vector<Order> matcher;

bool is_match(vector<int> & arr, int begin, int match, Order & order) {
    if(order.same != inf && arr[begin + order.same] != arr[begin + match]) return false;
    if(order.lo != inf && arr[begin + order.lo] >= arr[begin + match]) return false;
    if(order.hi != inf && arr[begin + order.hi] <= arr[begin + match]) return false;
    return true;
}

vector<int> get_fail(vector<int> & P) {

    vector<int> nxt(m), prev(m), count(m, 0), head(m, inf);
    for(int i = 0; i < m; i++) {
        nxt[i] = i + 1; prev[i] = i - 1;
        count[P[i]]++;
        if(head[P[i]] == inf) head[P[i]] = i;
    }

    matcher = vector<Order> (m, { inf, inf, inf });
    for(int i = m - 1; 0 <= i; i--) {   
        
        int rank = P[i];

        if(2 <= count[rank]) matcher[i].same = head[rank];
        
        int lo = prev[rank], hi = nxt[rank];
        if(lo != -1) matcher[i].lo = head[lo];
        if(hi != m) matcher[i].hi = head[hi];

        count[rank]--;        

        if(!count[rank]) {
            if(prev[rank] != -1) nxt[prev[rank]] = nxt[rank];
            if(nxt[rank] != m) prev[nxt[rank]] = prev[rank];
        }

    }

    vector<int> ret(m, 0);
    int begin = 1, match = 0;
    while(begin + match < m) {
        if(is_match(P, begin, match, matcher[match])) {
            match++;
            ret[begin + match - 1] = match;
        }
        else {
            if(match == 0) begin++;
            else {
                begin += (match - ret[match - 1]);
                match = ret[match - 1];
            }
        }
    }


    return ret;

}

vector<int> KMP(vector<int> & H, vector<int> & P) {

    vector<int> fail = get_fail(P);
    
    vector<int> ret;
    int begin = 0, match = 0;
    while(begin <= n - m) {
        if(match < m && is_match(H, begin, match, matcher[match])) {
            ++match;
            if(match == m) ret.push_back(begin + 1);
        }
        else {
            if(match == 0) begin++;
            else {
                begin += (match - fail[match - 1]);
                match = fail[match - 1];
            }
        }
    }

    return ret;

}

void compress(vector<int> & origin) {

    auto compress = [&](vector<int> & arr) {
        vector<int> order(arr.begin(), arr.end());
        sort(order.begin(), order.end());
        order.erase(unique(order.begin(), order.end()), order.end());
        for(auto & rank: arr) rank = lower_bound(order.begin(), order.end(), rank) - order.begin();
    };

    compress(origin);

}

int main() {

    fastio;

    cin >> m >> n;
    pattern = vector<int> (m); chart = vector<int> (n);

    for(auto & val: pattern) cin >> val;
    for(auto & val: chart) cin >> val;

    compress(pattern);
    auto answer = KMP(chart, pattern);

    if(answer.empty()) cout << "0" << endl;
    else {
        for(auto ans: answer) cout << ans << " ";
        cout << endl;
    }
    

}