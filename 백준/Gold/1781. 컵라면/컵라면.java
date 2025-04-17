import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class Main {

    static int N, P, C;

    public static void main(String[] args) throws Exception {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken());

        PriorityQueue<int []> pq = new PriorityQueue<>(new Comparator<int[]>() {
            @Override
            public int compare(int[] o1, int[] o2) {
                if(o1[0] == o2[0]) {
                    return o2[1] - o1[1];
                }
                return o1[0] - o2[0];
            }
        });

        for(int idx=0; idx<N; idx++) {
            st = new StringTokenizer(br.readLine());
            P = Integer.parseInt(st.nextToken());
            C = Integer.parseInt(st.nextToken());

            pq.add(new int[]{P, C});
        }

        PriorityQueue<Integer> solve = new PriorityQueue<>();

        int current = 1;
        while(!pq.isEmpty()) {
            int [] problem = pq.poll();

            if(solve.size() <= problem[0]) {
                if(solve.size() == problem[0] && solve.peek() < problem[1]) {
                    solve.poll();
                    solve.add(problem[1]);
                }
                else if(solve.size() < problem[0]) {
                    solve.add(problem[1]);
                }
            }
        }

        long answer = 0L;
        while(!solve.isEmpty()) {
            answer += solve.poll();
        }

        System.out.println(answer);
    }
}
