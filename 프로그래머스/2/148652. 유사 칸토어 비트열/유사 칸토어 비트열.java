class Solution {
    long[] pow5 = new long[21];
    long[] pow4 = new long[21];
    long L, R;

    public int solution(int n, long l, long r) {
        L = l;
        R = r;

        pow5[0] = 1;
        pow4[0] = 1;
        for (int i = 1; i <= 20; i++) {
            pow5[i] = pow5[i - 1] * 5L;
            pow4[i] = pow4[i - 1] * 4L;
        }

        return (int) dfs(0, 1, pow5[n], true, n);
    }

    long dfs(int depth, long s, long e, boolean one, int n) {
        if (!one) return 0;

        if (R < s || e < L) return 0;

        if (L <= s && e <= R) {
            return pow4[n - depth];
        }

        if (depth == n) {
            return 1;
        }

        long len = (e - s + 1) / 5;
        long ret = 0;

        for (int i = 0; i < 5; i++) {
            long ns = s + i * len;
            long ne = ns + len - 1;
            boolean childOne = (i != 2);

            ret += dfs(depth + 1, ns, ne, childOne, n);
        }

        return ret;
    }
}