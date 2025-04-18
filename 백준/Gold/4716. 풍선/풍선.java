import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class Main {

    static int N, A, B, K, DA, DB;

    public static void main(String[] args) throws Exception {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        while(true) {

            StringTokenizer st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());
            A = Integer.parseInt(st.nextToken());
            B = Integer.parseInt(st.nextToken());

            if(N == 0 && A == 0 && B == 0)
                break;

            PriorityQueue<int []> pq = new PriorityQueue<>(new Comparator<int[]>() {
                @Override
                public int compare(int[] o1, int[] o2) {
                    return Math.abs(o2[1] - o2[2]) - Math.abs(o1[1] - o1[2]);
                }
            });

            for(int idx=0; idx<N; idx++) {
                st = new StringTokenizer(br.readLine());
                K = Integer.parseInt(st.nextToken());
                DA = Integer.parseInt(st.nextToken());
                DB = Integer.parseInt(st.nextToken());

                pq.add(new int[]{K, DA, DB});
            }

            long answer = 0L;
            while(!pq.isEmpty()) {
                int need = pq.peek()[0];
                int rA = pq.peek()[1];
                int rB = pq.peek()[2];

                pq.poll();

                int getA, getB;
                if(rA < rB) {
                    getA = Math.min(A, need);
                    getB = Math.min(B, need - getA);

                }
                else {
                    getB = Math.min(B, need);
                    getA = Math.min(A, need - getB);
                }

                answer += ((long) getA * rA + (long) getB * rB);
                A -= getA;
                B -= getB;
            }

            System.out.println(answer);
        }
    }
}
