#include <iostream>
#include <vector>
#include <string>

#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;

int N;
string P;
vector<vector<pair<int, char>>> tree;
vector<int> fail;
vector<vector<int>> automaton;

// 실패 함수 생성
vector<int> get_fail() {

    int m = P.size();
    vector<int> ret(m, 0);
    
    int begin = 1, match = 0;
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


vector<vector<int>> build_automaton(const string &P, const vector<int> & fail) {
    int m = P.size();
    vector<vector<int>> aut(m + 1, vector<int>(26, 0));

    for (int state = 0; state <= m; ++state) {
        for (char ch = 'a'; ch <= 'z'; ++ch) {
            if (state < m && ch == P[state]) {
                aut[state][ch - 'a'] = state + 1;
            } else if (state > 0) {
                aut[state][ch - 'a'] = aut[fail[state - 1]][ch - 'a'];
            } else {
                aut[state][ch - 'a'] = 0;
            }
        }
    }

    return aut;
}


int dfs(int node, int match) {
    int count = 0;
    if (match == P.size()) count++;

    for (auto &[next, ch] : tree[node])
        count += dfs(next, automaton[match][ch - 'a']);

    return count;
}

int main() {
    fastio;

    cin >> N;
    tree.resize(N + 1);

    for (int i = 0; i < N - 1; i++) {
        int u, v; char c;
        cin >> u >> v >> c;
        tree[u].emplace_back(v, c);
    }

    cin >> P;
    fail = get_fail();
    automaton = build_automaton(P, fail);

    int answer = dfs(1, 0);
    cout << answer << '\n';
}
