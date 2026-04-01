import java.util.function.Function;
import java.util.*;

class Solution {

    int w;
    int[] a;
    int[][] cost;
    int[][] pick;

    static final int inf = (int) 1e9;

    int dfs(int l, int r) {
        if (l > r) return 0;
        if (l == r) {
            pick[l][r] = l;
            return cost[l][r] = a[l];
        }

        if (cost[l][r] != -1) return cost[l][r];

        cost[l][r] = inf;

        for (int i = l; i <= r; i++) {
            int left = dfs(l, i - 1);
            int right = dfs(i + 1, r);

            int worst = Math.max(a[i], Math.max(a[i] + left, a[i] + right));

            if (worst < cost[l][r]) {
                cost[l][r] = worst;
                pick[l][r] = i;
            }
        }

        return cost[l][r];
    }

    public int solution(int[] depth, int money, Function<Integer, Integer> excavate) {

        w = depth.length;

        a = new int[w + 1];
        for (int i = 1; i <= w; i++) {
            a[i] = depth[i - 1];
        }

        cost = new int[w + 2][w + 2];
        pick = new int[w + 2][w + 2];

        for (int i = 0; i <= w + 1; i++) {
            Arrays.fill(cost[i], -1);
        }

        dfs(1, w);

        int l = 1;
        int r = w;

        while (l <= r) {
            int now = pick[l][r];
            int res = excavate.apply(now);

            if (res == 0) return now;
            if (res < 0) r = now - 1;
            else l = now + 1;
        }

        return -1;
    }
}