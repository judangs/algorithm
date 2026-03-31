import java.util.*;

class Solution {
    static class Pos {
        int y, x;
        Pos(int y, int x) {
            this.y = y;
            this.x = x;
        }
    }

    int m, n;
    char[][] map;
    Pos[][] pos = new Pos[26][2];
    int[] cnt = new int[26];
    boolean[] exist = new boolean[26];
    int[] letterBit = new int[26];
    int letterCount;

    List<Integer>[] routeMasks = new ArrayList[26];
    Map<Integer, String> memo = new HashMap<>();

    public String solution(int m, int n, String[] board) {
        this.m = m;
        this.n = n;
        this.map = new char[m][n];

        for (int i = 0; i < 26; i++) {
            routeMasks[i] = new ArrayList<>();
            letterBit[i] = -1;
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                char c = board[i].charAt(j);
                map[i][j] = c;
                if ('A' <= c && c <= 'Z') {
                    int idx = c - 'A';
                    pos[idx][cnt[idx]++] = new Pos(i, j);
                    exist[idx] = true;
                }
            }
        }

        int bit = 0;
        for (int i = 0; i < 26; i++) {
            if (exist[i]) {
                letterBit[i] = bit++;
            }
        }
        letterCount = bit;

        for (int i = 0; i < 26; i++) {
            if (!exist[i]) continue;
            buildRoutes(i);
            if (routeMasks[i].isEmpty()) {
                return "IMPOSSIBLE";
            }
        }

        String ans = dfs(0);
        return ans == null ? "IMPOSSIBLE" : ans;
    }

    String dfs(int removedMask) {
        if (Integer.bitCount(removedMask) == letterCount) {
            return "";
        }

        if (memo.containsKey(removedMask)) {
            return memo.get(removedMask);
        }

        for (int i = 0; i < 26; i++) {
            if (!exist[i]) continue;

            int bit = 1 << letterBit[i];
            if ((removedMask & bit) != 0) continue;

            boolean canRemove = false;
            for (int needMask : routeMasks[i]) {
                if ((needMask & ~removedMask) == 0) {
                    canRemove = true;
                    break;
                }
            }

            if (!canRemove) continue;

            String next = dfs(removedMask | bit);
            if (next != null) {
                String ret = (char)('A' + i) + next;
                memo.put(removedMask, ret);
                return ret;
            }
        }

        memo.put(removedMask, null);
        return null;
    }

    void buildRoutes(int alpha) {
        Pos a = pos[alpha][0];
        Pos b = pos[alpha][1];

        if (a.y == b.y || a.x == b.x) {
            int mask = collectStraight(a.y, a.x, b.y, b.x, alpha);
            if (mask != -1) {
                routeMasks[alpha].add(mask);
            }
            return;
        }

        int mask1 = collectTurn(a, b, a.y, b.x, alpha);
        if (mask1 != -1) {
            routeMasks[alpha].add(mask1);
        }

        int mask2 = collectTurn(a, b, b.y, a.x, alpha);
        if (mask2 != -1 && !routeMasks[alpha].contains(mask2)) {
            routeMasks[alpha].add(mask2);
        }
    }

    int collectTurn(Pos a, Pos b, int cy, int cx, int alpha) {
        if (!isInside(cy, cx)) return -1;
        if (map[cy][cx] == '*') return -1;

        int mask1 = collectStraight(a.y, a.x, cy, cx, alpha);
        if (mask1 == -1) return -1;

        int mask2 = collectStraight(cy, cx, b.y, b.x, alpha);
        if (mask2 == -1) return -1;

        int mask = mask1 | mask2;

        if (!(cy == a.y && cx == a.x) && !(cy == b.y && cx == b.x)) {
            char c = map[cy][cx];
            if (c == '*') return -1;
            if ('A' <= c && c <= 'Z' && c - 'A' != alpha) {
                mask |= 1 << letterBit[c - 'A'];
            }
        }

        return mask;
    }

    int collectStraight(int y1, int x1, int y2, int x2, int alpha) {
        int mask = 0;

        if (y1 == y2) {
            int s = Math.min(x1, x2);
            int e = Math.max(x1, x2);
            for (int x = s; x <= e; x++) {
                if ((y1 == y1 && x == x1) || (y2 == y1 && x == x2)) continue;
                char c = map[y1][x];
                if (c == '*') return -1;
                if ('A' <= c && c <= 'Z') {
                    int idx = c - 'A';
                    if (idx != alpha) {
                        mask |= 1 << letterBit[idx];
                    }
                }
            }
            return mask;
        }

        if (x1 == x2) {
            int s = Math.min(y1, y2);
            int e = Math.max(y1, y2);
            for (int y = s; y <= e; y++) {
                if ((y == y1 && x1 == x1) || (y == y2 && x2 == x1)) continue;
                char c = map[y][x1];
                if (c == '*') return -1;
                if ('A' <= c && c <= 'Z') {
                    int idx = c - 'A';
                    if (idx != alpha) {
                        mask |= 1 << letterBit[idx];
                    }
                }
            }
            return mask;
        }

        return -1;
    }

    boolean isInside(int y, int x) {
        return 0 <= y && y < m && 0 <= x && x < n;
    }
}