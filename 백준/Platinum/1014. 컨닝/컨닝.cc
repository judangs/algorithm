#include <iostream>
#include <vector>

using namespace std;

int C, N, M;

static int dy[] = {-1, -1, 0, 0, 1, 1};
static int dx[] = {-1, 1, -1, 1, -1, 1};


bool binmatch(int current, vector<vector<int>> & graph, vector<bool> & visit, vector<int> & match) {
    for(auto next: graph[current]) {
        if(visit[next] == false) {
            visit[next] = true;
            
            if(match[next] == -1 || binmatch(match[next], graph, visit, match)) {
                match[next] = current;
                return true;
            }
        }
    }

    return false;
}


bool check(int y, int x) {
    return 0 <= y && y < N && 0 <= x && x < M;
}

int main() {

    cin >> C;
    while(C--) {
        cin >> N >> M;

        int max_node = 20 * (N + 1) + (M + 1);

        vector<vector<char>> seats(N, vector<char>(M));
        vector<vector<int>> graph(max_node);
        vector<int> match(max_node, - 1);

        int blank = 0;
        for(int i=0; i<N; i++) {
            for(int j=0; j<M; j++) {
                cin >> seats[i][j];
                if(seats[i][j] == '.')
                    blank++;
            }
        }

        for(int i=0; i<N; i++) {
            for(int j=0; j<M; j++) {
                for(int k=0; k<6; k++) {
                    int current = 20 * i + j;
                    if(seats[i][j] == '.') {
                        if(check(i + dy[k], j + dx[k]) && seats[i + dy[k]][j + dx[k]] == '.') {
                            int next = 20 * (i + dy[k]) + (j + dx[k]);
                            graph[current].push_back(next);
                        }
                    }
                }
            }
        }

        vector<bool> visit(max_node, false);

        int cheat = 0;
        for(int i=0; i<N; i++) {
            for(int j=0; j<M; j++) {
                fill(visit.begin(), visit.end(), false);
                if(binmatch(20 * i + j, graph, visit, match))
                    cheat++;
            }
        }        

        cout << (blank - cheat / 2) << "\n";
    }
    
}