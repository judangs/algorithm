#include <string>
#include <vector>
#include <queue>
#include <iostream>

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

using namespace std;

static int dx[] = {1, 0, -1, 0};
static int dy[] = {0, 1, 0, -1};

struct Pos {
    int y;
    int x;
    int state;
};

struct Robot {
    Pos front;
    Pos back;
    int cost;
    
    Robot(Pos front, Pos back, int cost) : front(front), back(back), cost(cost) { };
};

queue<Robot> q;
bool visit[101][101][4] = {false, };

bool check_range_with_feild(Pos & part1, Pos & part2, vector<vector<int>> & board) {
    int N = board.size();
    if(part1.y < 0 || part1.y >= N || part2.y < 0 || part2.y >= N) return false;
    if(part1.x < 0 || part1.x >= N || part2.x < 0 || part2.x >= N) return false;

    if(board[part1.y][part1.x] == 0 && board[part2.y][part2.x] == 0) return true;
    return false;
}

int solution(vector<vector<int>> board) {

    int N = board.size();
    Robot init = {{0, 0, LEFT}, {0, 1, RIGHT}, 0};
    visit[0][0][LEFT] = true;
    visit[0][1][RIGHT] = true;
    q.push(init);
    
    while(!q.empty()) {
        Pos part1 = q.front().front;
        Pos part2 = q.front().back;
        int cost = q.front().cost;

        q.pop();

        if((part1.y == N-1 && part1.x == N-1) || (part2.y == N-1 && part2.x == N-1))
            return cost;

        for(int k=0; k<4; k++) {
            Pos next_part1 = {part1.y + dy[k], part1.x + dx[k], part1.state};
            Pos next_part2 = {part2.y + dy[k], part2.x + dx[k], part2.state};

            if(check_range_with_feild(next_part1, next_part2, board) == false) continue;
            if(visit[next_part1.y][next_part1.x][next_part1.state] == false && visit[next_part2.y][next_part2.x][next_part2.state] == false) {
                Robot next = {next_part1, next_part2, cost + 1};
                q.push(next);
                visit[next.front.y][next.front.x][next.front.state] = true;
                visit[next.back.y][next.back.x][next.back.state] = true;
            }
        }

        if(part1.state == LEFT) {
            Pos up_left = {part1.y - 1, part1.x, UP};
            Pos up_right = {part2.y - 1, part2.x, UP};
            if(check_range_with_feild(up_left, up_right, board)) {
                Pos turn_left = {part1.y, part1.x, DOWN};
                if(visit[up_left.y][up_left.x][up_left.state] == false && visit[turn_left.y][turn_left.x][turn_left.state] == false) {
                    Robot next = {up_left, turn_left, cost + 1};
                    q.push(next);
                    visit[next.front.y][next.front.x][next.front.state] = true;
                    visit[next.back.y][next.back.x][next.back.state] = true;                    
                }

                Pos turn_right = {part2.y, part2.x, DOWN};
                if(visit[up_right.y][up_right.x][up_right.state] == false && visit[turn_right.y][turn_right.x][turn_right.state] == false) {
                    Robot next = {up_right, turn_right, cost + 1};
                    q.push(next);
                    visit[next.front.y][next.front.x][next.front.state] = true;
                    visit[next.back.y][next.back.x][next.back.state] = true;
                }
            }

            Pos down_left = {part1.y + 1, part1.x, DOWN};
            Pos down_right = {part2.y + 1, part2.x, DOWN};
            if(check_range_with_feild(down_left, down_right, board)) {
                Pos turn_left = {part1.y, part1.x, UP};
                if(visit[down_left.y][down_left.x][down_left.state] == false && visit[turn_left.y][turn_left.x][turn_left.state] == false) {
                    Robot next = {turn_left, down_left, cost + 1};
                    q.push(next);
                    visit[next.front.y][next.front.x][next.front.state] = true;
                    visit[next.back.y][next.back.x][next.back.state] = true;                    
                }

                Pos turn_right = {part2.y, part2.x, UP};
                if(visit[down_right.y][down_right.x][down_right.state] == false && visit[turn_right.y][turn_right.x][turn_right.state] == false) {
                    Robot next = {turn_right, down_right, cost + 1};
                    q.push(next);
                    visit[next.front.y][next.front.x][next.front.state] = true;
                    visit[next.back.y][next.back.x][next.back.state] = true;
                }
            }
        }
        
        if(part1.state == UP) {
            Pos left_up = {part1.y, part1.x - 1, LEFT};
            Pos left_down = {part2.y, part2.x - 1, LEFT};

            if(check_range_with_feild(left_up, left_down, board)) {
                Pos turn_left = {part1.y, part1.x, RIGHT};
                if(visit[left_up.y][left_up.x][left_up.state] == false && visit[turn_left.y][turn_left.x][turn_left.state] == false) {
                    Robot next = {left_up, turn_left, cost  + 1};
                    q.push(next);
                    visit[next.front.y][next.front.x][next.front.state] = true;
                    visit[next.back.y][next.back.x][next.back.state] = true;                    
                }

                Pos turn_right = {part2.y, part2.x, RIGHT};
                if(visit[left_down.y][left_down.x][left_down.state] == false && visit[turn_right.y][turn_right.x][turn_right.state] == false) {
                    Robot next = {left_down, turn_right, cost  + 1};
                    q.push(next);
                    visit[next.front.y][next.front.x][next.front.state] = true;
                    visit[next.back.y][next.back.x][next.back.state] = true;                    
                }                
            }

            Pos right_up = {part1.y, part1.x + 1, RIGHT};
            Pos right_down = {part2.y, part2.x + 1, RIGHT};

            if(check_range_with_feild(right_up, right_down, board)) {
                Pos turn_left = {part1.y, part1.x, LEFT};
                if(visit[right_up.y][right_up.x][right_up.state] == false && visit[turn_left.y][turn_left.x][turn_left.state] == false) {
                    Robot next = {turn_left, right_up, cost  + 1};
                    q.push(next);
                    visit[next.front.y][next.front.x][next.front.state] = true;
                    visit[next.back.y][next.back.x][next.back.state] = true;                    
                }

                Pos turn_right = {part2.y, part2.x, LEFT};
                if(visit[right_down.y][right_down.x][right_down.state] == false && visit[turn_right.y][turn_right.x][turn_right.state] == false) {
                    Robot next = {turn_right, right_down, cost  + 1};
                    q.push(next);
                    visit[next.front.y][next.front.x][next.front.state] = true;
                    visit[next.back.y][next.back.x][next.back.state] = true;                    
                }                   
            }
        }
    }
    
    
    
}

int main() {
    vector<vector<int>> board = {{0, 0, 0, 1, 1},{0, 0, 0, 1, 0},{0, 1, 0, 1, 1},{1, 1, 0, 0, 1},{0, 0, 0, 0, 0}};
    cout << solution(board);
}