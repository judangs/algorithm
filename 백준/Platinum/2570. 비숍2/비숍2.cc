#include <iostream>
#include <vector>

using namespace std;

int N, M, by, bx;

static int dy[] = {1, 1};
static int dx[] = {1, -1};

vector<vector<int>> board;
vector<vector<int>> node[2];

vector<vector<int>> adj;
vector<int> matched;


bool is_range(int y, int x) {
    return 0 <= y && y < N && 0 <= x && x < N;
}


bool matching(int current, vector<bool> & visit) {
    for(auto next: adj[current]) {
        if(!visit[next]) {
            visit[next] = true;
            
            if(matched[next] == -1 || matching(matched[next], visit)) {
                matched[next] = current;
                return true;
            }
        }
    }

    return false;
}


int main() {

    cin >> N >> M;
    board.resize(N, vector<int>(N, 1));
    for(int dir=0; dir<2; dir++)
        node[dir].resize(N, vector<int>(N, 0));
    
    while(M--) {
        cin >> by >> bx;
        board[by - 1][bx - 1] = 0;
    }

    int g = 1;
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            if(board[i][j] == 1) {
                for(int dir=0; dir<2; dir++) {
                    if(node[dir][i][j] != 0) continue;
                    int cy = i, cx = j;
                    while(is_range(cy, cx) && board[cy][cx] != 0) {
                        node[dir][cy][cx] = g;
                        cy += dy[dir], cx += dx[dir];
                    }

                    g++;
                }
            }
        }
    }

    adj.resize(g + 1);
    for(int y=0; y<N; y++) {
        for(int x=0; x<N; x++) {
            if(board[y][x]) {
                adj[node[0][y][x]].push_back(node[1][y][x]);
            }
        }
    }
    
    
    matched.resize(g, -1);

    int answer = 0;
    for(int vertex = 1; vertex < g; vertex++) {
        vector<bool> visit(g, false);
        if(matching(vertex, visit))
            answer++;
    }

    cout << answer;
}