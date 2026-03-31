import java.util.*;

class Solution {

    static class Pos {
        int y, x;
        Pos(int y, int x) {
            this.y = y;
            this.x = x;
        }
    }

    static int[][][] SHAPES = {
        {{0, 0}, {1, 0}, {1, 1}, {1, 2}},
        {{0, 0}, {1, 0}, {2, 0}, {2, -1}},
        {{0, 0}, {1, 0}, {2, 0}, {2, 1}},
        {{0, 0}, {0, 1}, {0, 2}, {-1, 2}},
        {{0, 0}, {0, 1}, {0, 2}, {-1, 1}}
    };

    static int[][][] NEEDS = {
        {{0, 1}, {0, 2}},
        {{0, -1}, {1, -1}},
        {{0, 1}, {1, 1}},
        {{-1, 0}, {-1, 1}},
        {{-1, 0}, {-1, 2}}
    };

    public int solution(int[][] board) {
        int n = board.length;
        int answer = 0;

        while (true) {
            boolean removedAny = false;
            boolean[][] visited = new boolean[n][n];

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (board[i][j] == 0 || visited[i][j]) continue;

                    int num = board[i][j];
                    List<Pos> cells = collectBlock(board, visited, i, j, num);

                    if (cells.size() != 4) continue;

                    int shapeIdx = matchShape(cells);
                    if (shapeIdx == -1) continue;

                    Pos anchor = findAnchor(cells, shapeIdx);
                    if (anchor == null) continue;

                    if (canRemove(board, anchor, shapeIdx)) {
                        removeBlock(board, num);
                        answer++;
                        removedAny = true;
                    }
                }
            }

            if (!removedAny) break;
        }

        return answer;
    }

    private List<Pos> collectBlock(int[][] board, boolean[][] visited, int sy, int sx, int num) {
        int n = board.length;
        int[] dy = {-1, 1, 0, 0};
        int[] dx = {0, 0, -1, 1};

        Queue<Pos> q = new LinkedList<>();
        List<Pos> cells = new ArrayList<>();

        q.offer(new Pos(sy, sx));
        visited[sy][sx] = true;

        while (!q.isEmpty()) {
            Pos cur = q.poll();
            cells.add(cur);

            for (int d = 0; d < 4; d++) {
                int ny = cur.y + dy[d];
                int nx = cur.x + dx[d];

                if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
                if (visited[ny][nx]) continue;
                if (board[ny][nx] != num) continue;

                visited[ny][nx] = true;
                q.offer(new Pos(ny, nx));
            }
        }

        return cells;
    }

    private int matchShape(List<Pos> cells) {
        for (Pos anchor : cells) {
            int[][] normalized = new int[4][2];
            for (int i = 0; i < 4; i++) {
                normalized[i][0] = cells.get(i).y - anchor.y;
                normalized[i][1] = cells.get(i).x - anchor.x;
            }

            sortCoords(normalized);

            for (int s = 0; s < SHAPES.length; s++) {
                int[][] target = copyShape(SHAPES[s]);
                sortCoords(target);

                if (sameCoords(normalized, target)) {
                    return s;
                }
            }
        }
        return -1;
    }

    private Pos findAnchor(List<Pos> cells, int shapeIdx) {
        for (Pos anchor : cells) {
            int[][] normalized = new int[4][2];
            for (int i = 0; i < 4; i++) {
                normalized[i][0] = cells.get(i).y - anchor.y;
                normalized[i][1] = cells.get(i).x - anchor.x;
            }

            sortCoords(normalized);

            int[][] target = copyShape(SHAPES[shapeIdx]);
            sortCoords(target);

            if (sameCoords(normalized, target)) {
                return anchor;
            }
        }
        return null;
    }

    private boolean canRemove(int[][] board, Pos anchor, int shapeIdx) {
        int n = board.length;

        for (int[] need : NEEDS[shapeIdx]) {
            int ny = anchor.y + need[0];
            int nx = anchor.x + need[1];

            if (ny < 0 || ny >= n || nx < 0 || nx >= n) return false;
            if (board[ny][nx] != 0) return false;
            if (!canDrop(board, ny, nx)) return false;
        }

        return true;
    }

    private boolean canDrop(int[][] board, int y, int x) {
        for (int i = 0; i < y; i++) {
            if (board[i][x] != 0) return false;
        }
        return true;
    }

    private void removeBlock(int[][] board, int num) {
        int n = board.length;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == num) {
                    board[i][j] = 0;
                }
            }
        }
    }

    private void sortCoords(int[][] arr) {
        Arrays.sort(arr, (a, b) -> {
            if (a[0] == b[0]) return Integer.compare(a[1], b[1]);
            return Integer.compare(a[0], b[0]);
        });
    }

    private boolean sameCoords(int[][] a, int[][] b) {
        for (int i = 0; i < a.length; i++) {
            if (a[i][0] != b[i][0] || a[i][1] != b[i][1]) {
                return false;
            }
        }
        return true;
    }

    private int[][] copyShape(int[][] shape) {
        int[][] copy = new int[shape.length][2];
        for (int i = 0; i < shape.length; i++) {
            copy[i][0] = shape[i][0];
            copy[i][1] = shape[i][1];
        }
        return copy;
    }
}