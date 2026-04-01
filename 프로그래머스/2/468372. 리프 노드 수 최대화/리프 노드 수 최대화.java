class Solution {

    public int solution(int dist_limit, int split_limit) {
        long answer = 1; // 분배를 하나도 안 하면 루트의 자식 1개가 리프

        for (long pow2 = 1, i = 0; pow2 <= split_limit; pow2 *= 2, i++) {
            for (long pow3 = 1, j = 0; pow2 * pow3 <= split_limit; pow3 *= 3, j++) {
                answer = Math.max(answer, simulate(dist_limit, (int)i, (int)j));
            }
        }

        return (int) answer;
    }

    long simulate(long distLimit, int twoCnt, int threeCnt) {
        long leaves = 1;
        long frontier = 1;

        for (int t = 0; t < twoCnt; t++) {
            if (distLimit >= frontier) {
                distLimit -= frontier;
                leaves += frontier;
                frontier *= 2;
            } else {
                leaves += distLimit;
                return leaves;
            }
        }

        for (int t = 0; t < threeCnt; t++) {
            if (distLimit >= frontier) {
                distLimit -= frontier;
                leaves += frontier * 2;
                frontier *= 3;
            } else {
                leaves += distLimit * 2;
                return leaves;
            }
        }

        return leaves;
    }
}