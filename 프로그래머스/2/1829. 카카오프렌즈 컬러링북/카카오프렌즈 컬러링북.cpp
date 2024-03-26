#include <vector>
#include <queue>
#include <tuple>
#include <iostream>

using namespace std;

int visit[100][100];

static int dx[] = {1, 0, -1, 0};
static int dy[] = {0, 1, 0, -1};

bool check_range(int y, int x, vector<vector<int>> & picture) {
    return 0 <= y && y < picture.size() && 0 <= x && x < picture[0].size();
}

int bfs(int y, int x, vector<vector<int>> & picture) {
    queue<tuple<int, int, int>> q;
    q.push(make_tuple(y, x, 0));
    visit[y][x] = true;
    
    int ret = 1;
    
    while(!q.empty()) {
        int current_y, current_x, cost;
        tie(current_y, current_x, cost) = q.front();
        
        
        q.pop();
           
        for(int k=0; k<4; k++) {
            int next_y = current_y + dy[k];
            int next_x = current_x + dx[k];
            
            if(check_range(next_y, next_x, picture) && visit[next_y][next_x] == false) {
                if(picture[current_y][current_x] == picture[next_y][next_x]) {
                    visit[next_y][next_x] = true;
                    q.push(make_tuple(next_y, next_x, cost + 1));
                    ret++;
                }
            }
        }
    }
    
    return ret;
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, vector<vector<int>> picture) {
    int number_of_area = 0;
    int max_size_of_one_area = 0;
    
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            visit[i][j] = false;
        }
    }
    
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            if(visit[i][j] == false && picture[i][j] != 0) {
                max_size_of_one_area = max(max_size_of_one_area, bfs(i, j, picture));
                number_of_area++;
            }
        }
    }
    
    vector<int> answer(2);
    answer[0] = number_of_area;
    answer[1] = max_size_of_one_area;
    return answer;
}