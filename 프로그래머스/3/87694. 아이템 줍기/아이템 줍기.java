import java.util.*;

class Solution {
    static class Node {
        int y, x, dist;

        Node(int y, int x, int dist) {
            this.y = y;
            this.x = x;
            this.dist = dist;
        }
    }

    static final int MAX = 102;
    static final int[] dy = {-1, 1, 0, 0};
    static final int[] dx = {0, 0, -1, 1};

    public int solution(int[][] rectangle, int characterX, int characterY, int itemX, int itemY) {
        int[][] board = new int[MAX][MAX];

        for (int[] r : rectangle) {
            int x1 = r[0] * 2;
            int y1 = r[1] * 2;
            int x2 = r[2] * 2;
            int y2 = r[3] * 2;

            for (int y = y1; y <= y2; y++) {
                for (int x = x1; x <= x2; x++) {
                    board[y][x] = 1;
                }
            }
        }

        for (int[] r : rectangle) {
            int x1 = r[0] * 2;
            int y1 = r[1] * 2;
            int x2 = r[2] * 2;
            int y2 = r[3] * 2;

            for (int y = y1 + 1; y < y2; y++) {
                for (int x = x1 + 1; x < x2; x++) {
                    board[y][x] = 0;
                }
            }
        }

        return bfs(board, characterY * 2, characterX * 2, itemY * 2, itemX * 2);
    }

    int bfs(int[][] board, int sy, int sx, int ey, int ex) {
        boolean[][] visit = new boolean[MAX][MAX];
        Queue<Node> q = new LinkedList<>();

        q.offer(new Node(sy, sx, 0));
        visit[sy][sx] = true;

        while (!q.isEmpty()) {
            Node now = q.poll();

            if (now.y == ey && now.x == ex) {
                return now.dist / 2;
            }

            for (int dir = 0; dir < 4; dir++) {
                int ny = now.y + dy[dir];
                int nx = now.x + dx[dir];

                if (ny < 0 || ny >= MAX || nx < 0 || nx >= MAX) continue;
                if (visit[ny][nx]) continue;
                if (board[ny][nx] != 1) continue;

                visit[ny][nx] = true;
                q.offer(new Node(ny, nx, now.dist + 1));
            }
        }

        return 0;
    }
}