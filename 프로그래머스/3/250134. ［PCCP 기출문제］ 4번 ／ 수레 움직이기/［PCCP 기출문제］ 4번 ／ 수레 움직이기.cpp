#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int inf = 1e9;
int n, m;
bool rvisit[5][5] = { false, };
bool bvisit[5][5] = { false, };

static int dy[] = { 0, 1, 0, -1};
static int dx[] = { 1, 0, -1, 0};

struct Pos {
    int y;
    int x;
    
    bool operator==(const Pos & o) const {
        return y == o.y && x == o.x;
    }   
    
    Pos move(int dir) {
        return Pos { y + dy[dir], x + dx[dir] };
    }
};

Pos rgoal, bgoal;

bool check(Pos red, Pos blue, bool rfix, bool bfix) {
    if(red.y < 0 || n <= red.y || red.x < 0 || m <= red.x) return false;
    if(blue.y < 0 || n <= blue.y || blue.x < 0 || m <= blue.x) return false;
    if(!rfix && rvisit[red.y][red.x]) return false;
    if(!bfix && bvisit[blue.y][blue.x]) return false;
    return true;
}

int solved(int turn, Pos red, Pos blue, vector<vector<int>> & maze) {
    
    if(red == rgoal && blue == bgoal) return turn;
    
    int ret = inf;
    
    bool rfix = false, bfix = false;
    if(red == rgoal) rfix = true;
    if(blue == bgoal) bfix = true;
    
    for(int rdir = 0; rdir < 4; rdir++) {
        for(int bdir = 0; bdir < 4; bdir++) {
            auto rnext = (rfix ? red : red.move(rdir));
            auto bnext = (bfix ? blue : blue.move(bdir));
            
            if(check(rnext, bnext, rfix, bfix)) {
                if(maze[rnext.y][rnext.x] != 5 && maze[bnext.y][bnext.x] != 5) {
                    
                    if(rnext == bnext) continue;
                    if(blue == rnext && red == bnext) continue;
                    
                    if(!(rnext == red)) 
                        rvisit[rnext.y][rnext.x] = true;
                    if(!(bnext == blue))
                        bvisit[bnext.y][bnext.x] = true;
                    ret = min(ret, solved(turn + 1, rnext, bnext, maze));
                    if(!(rnext == red)) 
                        rvisit[rnext.y][rnext.x] = false;
                    if(!(bnext == blue))
                        bvisit[bnext.y][bnext.x] = false;                                 
                }
            }
        }
    }
    
    return ret;
    
}

int solution(vector<vector<int>> maze) {
    
    n = maze.size(), m = maze.front().size();
    
    Pos red, blue;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(maze[i][j] == 1) red = Pos { i, j };
            if(maze[i][j] == 2) blue = Pos { i, j };
            if(maze[i][j] == 3) rgoal = Pos { i, j };
            if(maze[i][j] == 4) bgoal = Pos { i, j };
        }
    }
    
    rvisit[red.y][red.x] = true;
    bvisit[blue.y][blue.x] = true;
    
    int answer = solved(0, red, blue, maze);
    answer = (answer == inf ? 0 : answer);
    return answer;
    
    
    
}