import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class Main {

    static int N, L, P;

    public static void main(String[] args) throws Exception {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken());
        int [][] stations = new int[N][2];

        for(int i=0; i<N; i++) {
            st = new StringTokenizer(br.readLine());
            stations[i][0] = Integer.parseInt(st.nextToken());
            stations[i][1] = Integer.parseInt(st.nextToken());
        }

        Arrays.sort(stations, (a, b) -> Integer.compare(a[0], b[0]));

        st = new StringTokenizer(br.readLine());
        L = Integer.parseInt(st.nextToken());
        P = Integer.parseInt(st.nextToken());

        PriorityQueue<int []> pq = new PriorityQueue<>(new Comparator<int[]>() {
            @Override
            public int compare(int[] o1, int[] o2) {
                return o2[1] - o1[1];
            }
        });

        int idx = 0;

        boolean cango = true;
        int current = P, answer = 0;
        while(current < L) {
            while(idx < N && stations[idx][0] <= current) {
                pq.add(new int[]{stations[idx][0], stations[idx][1]});
                idx++;
            }

            if(pq.isEmpty()) {
                cango = false;
                break;
            }

            int [] station = pq.poll();
            current += station[1];
            answer += 1;
        }

        if(cango) System.out.println(answer);
        else System.out.println(-1);

    }
}
