#include <iostream>
#include <vector>

#define INF 1e9

using namespace std;

vector<vector<char>> bulb(10, vector<char>(10));
bool visited[1 << 10] = {0, };

static int dy[] = {0, 1, 0, -1};
static int dx[] = {1, 0, -1, 0};

bool check(int y, int x) {
    return 0 <= y && y < 10 && 0 <= x && x < 10;
}

void turnoff(vector<vector<char>> & current, int y, int x) {

    current[y][x] = (current[y][x] == 'O' ? '#' : 'O');

    for(int k=0; k<4; k++) {
        int ny = y + dy[k];
        int nx = x + dx[k];
        
        if(!check(ny, nx)) continue;
        current[ny][nx] = (current[ny][nx] == 'O' ? '#' : 'O');
    }

}

int turnoff(int select) {

    vector<vector<char>> current = bulb;

    int count = 0;
    for(int i=0; i<10; i++) {
        if((select & (1 << i)) != 0) {
            turnoff(current, 0, i);
            count++;
        }
    }

    for(int i=1; i<10; i++) {
        for(int j=0; j<10; j++) {
            if(current[i - 1][j] == 'O') {
                count++;
                turnoff(current, i, j);    
            }
        }
    }

    for(int i=0; i<10; i++) {
        for(int j=0; j<10; j++) {
            if(current[i][j] == 'O')
                return INF;
        }
    }

    return count;
}

int click() {

    int unit = 0;
    for(int idx=0; idx<10; idx++) {
        if(bulb[0][idx] == 'O') 
            unit |= (1 << idx);
    }

    int answer = INF;
    answer = min(answer, turnoff(0));
    for(int select=(1 << 10) - 1; select >= 0; select--) {
        answer = min(answer, turnoff(select));
    }

    return (answer == INF ? -1 : answer);
}

int main() {

    for(int i=0; i<10; i++) {
        for(int j=0; j<10; j++) {
            cin >> bulb[i][j];
        }
    }

    cout << click();
}