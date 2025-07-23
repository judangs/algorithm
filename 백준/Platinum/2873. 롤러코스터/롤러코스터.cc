#include <iostream>

#define INF 1e9

using namespace std;

int R, C;
int attraction[1001][1001];

int happy = INF, ey, ex;

string answer;

static int downleft[4][2] = {
    {1, 0}, {0, -1}, {-1, 0}, {0, -1} 
};

static int leftdown[4][2] = {
    {0, -1}, {1, 0}, {0, -1}, {-1, 0}
};
static int downright[4][2] = {
    {1, 0}, {0, 1}, {-1, 0}, {0, 1}
};
static int rightdown[4][2] = {
    {0, 1}, {1, 0}, {0, 1}, {-1, 0}
};

static char sddir[4] = {'D', 'L', 'U', 'L'};
static char sldir[4] = {'L', 'D', 'L', 'U'};

static char sdrdir[4] = {'D', 'R', 'U', 'R'};
static char srddir[4] = {'R', 'D', 'R', 'U'};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> R >> C;
    for(int i=1; i<=R; i++) {
        for(int j=1; j<=C; j++) {
            cin >> attraction[i][j];
            if(i % 2 != j % 2 && attraction[i][j] < happy) {
                happy = attraction[i][j]; ey = i, ex = j;
            }
        }
    }

    if(R % 2 ==1 || C % 2 == 1) {
        if(C % 2 == 0) {
            for(int cy = 1, cx = 1; !(cy == R && cx == C); ) {
                if(cx == 1) {
                    answer += string(C - 1, 'R');
                    cx = C;
                    if(cy != R) {
                        answer += 'D'; cy++;
                    }
                }
                else {
                    answer += string(C - 1, 'L') + 'D';
                    cx = 1; cy++;
                }
            }
        }
        else {
            
            for(int cy=1, cx = 1; !(cy == R && cx == C); ) {
                if(cy == 1) {
                    answer += string(R - 1, 'D');
                    cy = R;
                    if(cx != C) {
                        answer += 'R'; cx++;
                    }
                }
                else if(cy == R) {
                    answer += string(R - 1, 'U') + 'R';
                    cy = 1; cx++;
                }
            }

        }
    }

    if(R % 2 == 0 && C % 2 == 0) {

        if(R == 2 && C == 2) {
            if(attraction[1][2] < attraction[2][1]) cout << "DR" << endl;
            else cout << "RD" << endl;
            return 0;
        } 

        for(int cy = 1, cx = 1; !(cy == R && cx == C); ) {

            if(cy <= ey && ey <= cy + 1) {
                if(cy % 2 != 0) {
                    int sy = cy;
                    for(int unit = 0, ctx = 0; !(cy == sy + 1 && cx == C); ) {
                        int ny, nx;
                        if(unit == 0) {
                            ny = cy + downright[ctx % 4][0], nx = cx + downright[ctx % 4][1];
                        }
                        else {
                            ny = cy + rightdown[ctx % 4][0], nx = cx + rightdown[ctx % 4][1];
                        }

                        if(ny == ey && nx == ex) unit ^= 1;

                        if(unit == 0) {
                            answer += string(1, sdrdir[ctx % 4]) + string(1,sdrdir[(ctx + 1) % 4]);
                            cy = cy + downright[ctx % 4][0] + downright[(ctx + 1) % 4][0];
                            cx = cx + downright[ctx % 4][1] + downright[(ctx + 1) % 4][1];
                        }
                        else {
                            answer += string(1, srddir[ctx % 4]) + string(1, srddir[(ctx + 1) % 4]);
                            cy = cy + rightdown[ctx % 4][0] + rightdown[(ctx + 1) % 4][0];
                            cx = cx + rightdown[ctx % 4][1] + rightdown[(ctx + 1) % 4][1];
                        }

                        ctx += 2;
                    }

                    if(cy != R) {
                        answer += 'D'; cy++;
                    }
                }
                else {
                    int sy = cy;
                    for(int unit = 0, ctx = 0; !(cy == sy + 1 && ((cy % 2 == 1 && cx == 1) || (cy % 2 == 0 && cx == C))); ) {
                        int ny, nx;
                        if(unit == 0) {
                            ny = cy + downleft[ctx % 4][0], nx = cx + downleft[ctx % 4][1];
                        }
                        else {
                            ny = cy + leftdown[ctx % 4][0], nx = cx + leftdown[ctx % 4][1];
                        }

                        if(ny == ey && nx == ex) unit ^= 1;

                        if(unit == 0) {
                            answer += string(1, sddir[ctx % 4]) + string(1,sddir[(ctx + 1) % 4]);
                            cy = cy + downleft[ctx % 4][0] + downleft[(ctx + 1) % 4][0];
                            cx = cx + downleft[ctx % 4][1] + downleft[(ctx + 1) % 4][1];
                        }
                        else {
                            answer += string(1, sldir[ctx % 4]) + string(1, sldir[(ctx + 1) % 4]);
                            cy = cy + leftdown[ctx % 4][0] + leftdown[(ctx + 1) % 4][0];
                            cx = cx + leftdown[ctx % 4][1] + leftdown[(ctx + 1) % 4][1];
                        }

                        ctx += 2;
                    }

                    answer += 'D'; cy++;
                }
            }
            else {
                if(cx == 1) {
                    answer += string(C - 1, 'R');
                    cx = C;
                    if(cy != R) {
                        answer += 'D'; cy++;
                    }
                }
                else {
                    answer += string(C - 1, 'L') + 'D';
                    cx = 1; cy++;
                }
            }
        }
    }

    cout << answer << endl;

}