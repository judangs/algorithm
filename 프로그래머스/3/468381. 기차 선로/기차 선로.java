class Solution {
    static final int UP = 0;
    static final int RIGHT = 1;
    static final int DOWN = 2;
    static final int LEFT = 3;

    static final int[] DR = {-1, 0, 1, 0};
    static final int[] DC = {0, 1, 0, -1};

    // OUT[type][inDir] = 현재 칸에 inDir 변으로 들어왔을 때, 어느 변으로 나가는가
    static final int[][] OUT = {
        {-1, -1, -1, -1},
        {-1, LEFT, -1, RIGHT},     // 1: 좌우 직선
        {DOWN, -1, UP, -1},        // 2: 상하 직선
        {DOWN, LEFT, UP, RIGHT},   // 3: 십자
        {LEFT, -1, -1, UP},        // 4: 상-좌
        {RIGHT, UP, -1, -1},       // 5: 상-우
        {-1, DOWN, RIGHT, -1},     // 6: 우-하
        {-1, -1, LEFT, DOWN}       // 7: 좌-하
    };

    int n;
    int m;
    int[][] grid;
    boolean[][][] visitedState;
    int[][] usedMask;
    int answer;

    public int solution(int[][] grid) {
        n = grid.length;
        m = grid[0].length;

        this.grid = new int[n][m];
        for (int i = 0; i < n; i++) {
            this.grid[i] = grid[i].clone();
        }

        visitedState = new boolean[n][m][4];
        usedMask = new int[n][m];
        answer = 0;

        // (0,0)에서 오른쪽으로 출발 => 시작 칸에 왼쪽 변으로 들어온 것으로 처리
        dfs(0, 0, LEFT);

        return answer;
    }

    void dfs(int r, int c, int inDir) {
        if (r < 0 || r >= n || c < 0 || c >= m) return;
        if (grid[r][c] == -1) return;
        if (visitedState[r][c][inDir]) return;

        // 빈칸이면 지금 들어온 방향과 맞는 선로를 하나 놓아본다.
        if (grid[r][c] == 0) {
            for (int type = 1; type <= 7; type++) {
                if (OUT[type][inDir] == -1) continue;

                grid[r][c] = type;
                process(r, c, inDir);
                grid[r][c] = 0;
            }
            return;
        }

        // 이미 선로가 있으면 그 선로가 현재 진입 방향을 받아줄 수 있어야 한다.
        if (OUT[grid[r][c]][inDir] == -1) return;

        process(r, c, inDir);
    }

    void process(int r, int c, int inDir) {
        int type = grid[r][c];
        int prevMask = usedMask[r][c];

        if (type == 3) {
            // 3번 선로는 가로/세로를 각각 지나야 함
            if (inDir == LEFT || inDir == RIGHT) {
                usedMask[r][c] |= 1;   // horizontal
            } else {
                usedMask[r][c] |= 2;   // vertical
            }
        } else {
            usedMask[r][c] = 1;
        }

        visitedState[r][c][inDir] = true;

        if (r == n - 1 && c == m - 1) {
            if (isComplete()) {
                answer++;
            }
        } else {
            int outDir = OUT[type][inDir];
            int nr = r + DR[outDir];
            int nc = c + DC[outDir];

            // 다음 칸에는 현재 outDir의 반대쪽 변으로 들어감
            dfs(nr, nc, outDir ^ 2);
        }

        visitedState[r][c][inDir] = false;
        usedMask[r][c] = prevMask;
    }

    boolean isComplete() {
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                int type = grid[r][c];
                if (type <= 0) continue;

                if (type == 3) {
                    if (usedMask[r][c] != 3) return false;
                } else {
                    if (usedMask[r][c] == 0) return false;
                }
            }
        }
        return true;
    }
}
