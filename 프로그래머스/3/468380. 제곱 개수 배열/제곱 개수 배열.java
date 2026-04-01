import java.util.*;

class Solution {

    int n;
    int[] val;
    long[] cntPrefix;   // 각 구간 길이 누적합
    long[] sumPrefix;   // 각 구간 전체 합 누적합 = arr[i]^2 누적

    public long[] solution(int[] arr, long l, long r) {
        n = arr.length;
        val = arr;

        cntPrefix = new long[n + 1];
        sumPrefix = new long[n + 1];

        for (int i = 1; i <= n; i++) {
            cntPrefix[i] = cntPrefix[i - 1] + val[i - 1];
            sumPrefix[i] = sumPrefix[i - 1] + 1L * val[i - 1] * val[i - 1];
        }

        long w = r - l + 1;
        long K = rangeSum(l, r);
        long C = countWindowsWithSum(w, K);

        return new long[]{K, C};
    }

    long rangeSum(long l, long r) {
        int lg = findGroup(l);
        int rg = findGroup(r);

        if (lg == rg) {
            return 1L * val[lg - 1] * (r - l + 1);
        }

        long res = 0;

        long leftEnd = cntPrefix[lg];
        res += 1L * val[lg - 1] * (leftEnd - l + 1);

        if (lg + 1 <= rg - 1) {
            res += sumPrefix[rg - 1] - sumPrefix[lg];
        }

        long rightStart = cntPrefix[rg - 1] + 1;
        res += 1L * val[rg - 1] * (r - rightStart + 1);

        return res;
    }

    long countWindowsWithSum(long w, long K) {
        long totalLen = cntPrefix[n];
        long maxStart = totalLen - w + 1;
        if (maxStart <= 0) return 0;

        long s = 1;
        long nowSum = rangeSum(1, w);
        long answer = 0;

        while (s < maxStart) {
            int leftGroup = findGroup(s);
            int inGroup = findGroup(s + w);

            long segEnd1 = cntPrefix[leftGroup];
            long segEnd2 = cntPrefix[inGroup] - w;
            long segEnd = Math.min(maxStart - 1, Math.min(segEnd1, segEnd2));

            if (segEnd < s) segEnd = s;

            long m = segEnd - s + 1;

            long outValue = val[leftGroup - 1];
            long inValue = val[inGroup - 1];
            long delta = inValue - outValue;

            if (delta == 0) {
                if (nowSum == K) answer += m;
            } else {
                long diff = K - nowSum;
                if (diff % delta == 0) {
                    long t = diff / delta;
                    if (0 <= t && t < m) answer++;
                }
            }

            nowSum += m * delta;
            s += m;
        }

        if (nowSum == K) answer++;

        return answer;
    }

    int findGroup(long pos) {
        int lo = 1, hi = n;
        while (lo < hi) {
            int mid = (lo + hi) >>> 1;
            if (cntPrefix[mid] >= pos) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }
}