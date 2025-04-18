import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class Main {

    static int N, K;

    public static void main(String [] args) throws Exception {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        N = Integer.parseInt(st.nextToken());

        st = new StringTokenizer(br.readLine());
        K = Integer.parseInt(st.nextToken());

        int [] sensor = new int[N];

        st = new StringTokenizer(br.readLine());
        for(int idx=0; idx<N; idx++) {
            sensor[idx] = Integer.parseInt(st.nextToken());
        }

        Arrays.sort(sensor);

        PriorityQueue<Integer> pq = new PriorityQueue<>(new Comparator<Integer>() {
            @Override
            public int compare(Integer o1, Integer o2) {
                return o2 - o1;
            }
        });

        for(int idx=1; idx<N; idx++) {
            pq.add(sensor[idx] - sensor[idx - 1]);
        }

        int count = 0;
        while(count++ < K - 1 && !pq.isEmpty()) {
            pq.poll();
        }

        int answer = 0;
        while(!pq.isEmpty()) {
            answer += pq.poll();
        }

        System.out.println(answer);
    }
}
