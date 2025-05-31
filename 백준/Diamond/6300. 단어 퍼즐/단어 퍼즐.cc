#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

int L, C, W;
string word;
vector<string> board;

struct Node {
    int sy;
    int sx;
    int dir;
};

vector<string> words;
vector<vector<Node>> solved;

static int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};
static int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};

static int boundaryCheck[8][4] = {
    {0, 0, 1, 0},
    {0, 1, 1, 0},
    {0, 1, 0, 0},
    {1, 1, 0, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 1},
    {0, 0, 0, 1},
    {0, 0, 1, 1}
};

static int boundaryStartX[4] = {0, 0, 0, 1};
static int boundaryStartY[4] = {0, 0, 1, 0};

static int boundaryDirX[4] = {1, 0, 1, 0};
static int boundaryDirY[4] = {0, 1, 0, 1};

struct Trie {
    bool end;
    int widx;
    Trie * fail;
    Trie * next[26];

    Trie() : end(false) {
        for(int ch=0; ch<26; ch++) next[ch] = nullptr;
    }

    void insert(const char * w, int idx) {
        if(*w == '\0') {
            end = true;
            widx = idx;
            return;
        }

        int ch = *w - 'A';
        if(next[ch] == nullptr) next[ch] = new Trie();
        
        next[ch]->insert(w + 1, idx);
    }
};

bool is_range(int y, int x) {
    return 0 <= y && y < L && 0 <= x && x < C;
}

void build_failure_path(Trie * root) {
    queue<Trie *> q;

    root->fail = root;
    q.push(root);

    while(!q.empty()) {
        auto current = q.front(); q.pop();
        
        for(int ch=0; ch<26; ch++) {
            auto next = current->next[ch];
            if(next != nullptr) {
                if(current == root) next->fail = current;
                else {
                    auto failure = current->fail;
                    
                    while(failure != root && failure->next[ch] == nullptr)
                        failure = failure->fail;

                    if(failure->next[ch] != nullptr) failure = failure->next[ch];
                    next->fail = failure;
                }

                if(next->fail->end) {
                    next->end = true;
                    next->widx = next->fail->widx;
                }

                q.push(next);
            }
        }
    }   
}

void search_kmp_with_trie(Trie * root, int y, int x, int dir) {

    auto node = root;

    while(is_range(y, x)) {
        int ch = board[y][x] - 'A';
        
        if(node->next[ch] != nullptr) {
            node = node->next[ch];
            if(node->end) {
                int sy = y - dy[dir] * (words[node->widx].size() - 1);
                int sx = x - dx[dir] * (words[node->widx].size() - 1);
                solved[node->widx].push_back({ sy, sx, dir });
            }

            y += dy[dir], x += dx[dir];
        }
        else {
            if(node == root) {
                y += dy[dir], x += dx[dir];
            }
            node = node->fail;
        }
    }
    
}

void find(Trie * root) {

    for(int dir=0; dir<8; dir++) {
        for(int boundary=0; boundary<4; boundary++) {
            if(boundaryCheck[dir][boundary] == 0) continue;

            int sy = 0, sx = 0;
            if(boundaryStartY[boundary] != 0) sy = L - 1;
            if(boundaryStartX[boundary] != 0) sx = C - 1;

            while(is_range(sy, sx)) {
                search_kmp_with_trie(root, sy, sx, dir);
                sy += boundaryDirY[boundary], sx += boundaryDirX[boundary];
            }
        }
    }
    
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    Trie * trie = new Trie();

    cin >> L >> C >> W;
    for(int i=0; i<L; i++) {
        cin >> word;
        board.push_back(word);
    }
    
    solved.resize(W);
    for(int i=0; i<W; i++) {
        cin >> word;
        words.push_back(word);
        trie->insert(word.c_str(), i);
    }

    build_failure_path(trie);    
    find(trie);

    for(auto solve: solved) {
        sort(solve.begin(), solve.end(), [](Node & l, Node & r) {
            if(l.sy == r.sy && l.sx == r.sx) return l.dir < r.dir;
            if(l.sy == r.sy) return l.sx < r.sx;
            return l.sy < r.sy;
        });

        cout << solve.front().sy << " " << solve.front().sx << " " << (char)(solve.front().dir + 'A') << "\n";
    }
}