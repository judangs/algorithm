import java.util.*;

class Solution {

    static class Pos {
        int y, x;

        Pos(int y, int x) {
            this.y = y;
            this.x = x;
        }
    }

    static class Node {
        int y, x, dir, turn;

        Node(int y, int x, int dir, int turn) {
            this.y = y;
            this.x = x;
            this.dir = dir;
            this.turn = turn;
        }
    }

    int m, n;
    char[][] map;
    Pos[][] pos = new Pos[26][2];
    int[] cnt = new int[26];
    boolean[] exist = new boolean[26];
    int total;

    int[] dy = {-1, 0, 1, 0};
    int[] dx = {0, 1, 0, -1};

    public String solution(int m, int n, String[] board) {
        this.m = m;
        this.n = n;
        this.map = new char[m][n];

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                char c = board[i].charAt(j);
                map[i][j] = c;

                if ('A' <= c && c <= 'Z') {
                    int idx = c - 'A';
                    pos[idx][cnt[idx]++] = new Pos(i, j);
                    if (!exist[idx]) {
                        exist[idx] = true;
                        total++;
                    }
                }
            }
        }

        StringBuilder answer = new StringBuilder();
        int removed = 0;

        while (removed < total) {
            boolean found = false;

            for (int i = 0; i < 26; i++) {
                if (!exist[i]) continue;

                Pos a = pos[i][0];
                Pos b = pos[i][1];
                char target = (char) ('A' + i);

                if (map[a.y][a.x] != target) continue;
                if (map[b.y][b.x] != target) continue;

                if (!canRemove(a, b)) continue;

                map[a.y][a.x] = '.';
                map[b.y][b.x] = '.';
                answer.append(target);
                removed++;
                found = true;
                break;
            }

            if (!found) return "IMPOSSIBLE";
        }

        return answer.toString();
    }

    boolean canRemove(Pos start, Pos end) {
        boolean[][][] visited = new boolean[m][n][4];
        Queue<Node> q = new ArrayDeque<>();

        for (int d = 0; d < 4; d++) {
            int ny = start.y + dy[d];
            int nx = start.x + dx[d];

            if (!inRange(ny, nx)) continue;
            if (!canPass(ny, nx, end)) continue;

            visited[ny][nx][d] = true;
            q.offer(new Node(ny, nx, d, 0));
        }

        while (!q.isEmpty()) {
            Node cur = q.poll();

            if (cur.y == end.y && cur.x == end.x) {
                return true;
            }

            for (int nd = 0; nd < 4; nd++) {
                int nt = cur.turn + (cur.dir == nd ? 0 : 1);
                if (nt > 1) continue;

                int ny = cur.y + dy[nd];
                int nx = cur.x + dx[nd];

                if (!inRange(ny, nx)) continue;
                if (!canPass(ny, nx, end)) continue;
                if (visited[ny][nx][nd]) continue;

                visited[ny][nx][nd] = true;
                q.offer(new Node(ny, nx, nd, nt));
            }
        }

        return false;
    }

    boolean canPass(int y, int x, Pos end) {
        if (y == end.y && x == end.x) return true;
        return map[y][x] == '.';
    }

    boolean inRange(int y, int x) {
        return 0 <= y && y < m && 0 <= x && x < n;
    }
}