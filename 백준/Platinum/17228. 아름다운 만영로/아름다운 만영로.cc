#include <iostream>
#include <vector>

#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;

int N;
string P;
vector<vector<pair<int, char>>> tree;

vector<int> get_fail() {
    
    vector<int> ret(P.size(), 0);

    int begin = 1, match = 0, m = P.size();
    while(begin + match < m) {
        if(P[begin + match] == P[match]) {
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

pair<int, int> KMP(string H, int begin) {
    
    vector<int> fail = get_fail();
    
    int match = 0, n = H.size(), m = P.size();
    if(n < m) return {0, 0};

    int ret = 0, last = 0;
    while(begin <= n - m) {
        if(match < m && H[begin + match] == P[match]) {
            match++;
            if(match == m) {
                ret++; last = begin;
            }
        }
        else {
            if(match == 0) begin++;
            else {
                begin += (match - fail[match - 1]);
                match = fail[match - 1];
            }
        }
    }

    return {ret, last};
}

int dfs(int now, int parent, string path, int begin) {

    auto res = KMP(path, begin);
    int ret = res.first;

    for(auto next: tree[now]) {
        if(res.first == 0)
            ret += dfs(next.first, now, path + next.second, begin);
        else
            ret += dfs(next.first, now, path + next.second, res.second + 1);
    }

    return ret;

}

int main() {

    fastio;
    cin >> N;
    tree = vector<vector<pair<int, char>>> (N + 1);

    for(int i = 0; i < N - 1; i++) {
        int u, v; char c;
        cin >> u >> v >> c;
        tree[u].push_back({ v, c });
    }

    cin >> P;

    int answer = dfs(1, 0, "", 0);
    cout << answer << endl;
    

}