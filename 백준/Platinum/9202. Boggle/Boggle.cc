#include <iostream>
#include <vector>
#include <set>
#include <cstring>

using namespace std;

int w, b;
int cost[10];

int score = 0, counting = 0;
string longest = "";

static int dy[] = {0, 1, 0, -1, 1, 1, -1, -1};
static int dx[] = {1, 0, -1, 0, 1, -1, 1, -1};

set<string> words;

struct Trie {
    
    bool end;
    Trie * next[27];
    
    Trie() : end(false) {
        for(int ch=0; ch<27; ch++) next[ch] = nullptr;
    }

    void insert(const char * w) {
        if(*w == '\0') {
            end = true;
            return;
        }
        
        int ch = *w - 'A';
        if(next[ch] == nullptr) next[ch] = new Trie();
        next[ch]->insert(w + 1);
    }

    bool find(const char * w) {
        if(*w == '\0') return end;
        
        int ch = *w - 'A';
        if(next[ch] == nullptr) return false;
        return next[ch]->find(w + 1);
    }

}trie;


bool valid(int y, int x) {
    return 0 <= y && y < 4 && 0 <= x && x < 4;
}


void dfs(int depth, int y, int x, string now, vector<string> & board, vector<vector<bool>> & visit) {

    if(depth == 8) return;

    if(trie.find(now.c_str())) {
        if(words.find(now) == words.end()) {
            words.insert(now);

            int n = now.size(), m = longest.size();
            counting++; score += cost[n];

            if(m < n || (n == m && now < longest)) {
                longest = now;
            }
        }
    }

    for(int dir=0; dir<8; dir++) {
        int ny = y + dy[dir], nx = x + dx[dir];
        if(valid(ny, nx) && !visit[ny][nx]) {
            visit[ny][nx] = true;
            dfs(depth + 1, ny, nx, now + board[ny][nx], board, visit);
            visit[ny][nx] = false;
        }
    }
    
}


void _find(vector<string> & board) {

    
    score = 0, counting = 0;
    longest = "";
    
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            vector<vector<bool>> visit(4, vector<bool>(4, false));
            visit[i][j] = true;
            dfs(0, i, j, string(1, board[i][j]), board, visit);
        }
    }

    words.clear();
    cout << score << " " << longest << " " << counting << "\n";

}



int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cost[3] = cost[4] = 1;
    cost[5] = 2; cost[6] = 3;
    cost[7] = 5; cost[8] = 11;

    cin >> w;
    while(w--) {
        string dict; cin >> dict;
        trie.insert(dict.c_str());
    }

    cin >> b;
    while(b--) {
        vector<string> board(4);
        for(int i=0; i<4; i++) {
            cin >> board[i];
        }

        _find(board);
        
    }
    

}