import java.io.BufferedReader;
import java.io.InputStreamReader;

import java.util.*;

public class Main {

    static int N, K;

    public static void main(String[] args) throws Exception {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());

        int [] products = new int[K + 1];
        int [] lastusage = new int[K + 1];
        for(int item=1; item <= K; item++) {
            lastusage[item] = -1;
        }

        st = new StringTokenizer(br.readLine());
        for(int idx=1; idx<=K; idx++) {
            int product = Integer.parseInt(st.nextToken());
            products[idx] = product;
            lastusage[product] = idx;
        }

        int pick = 0;
        boolean [] visit = new boolean[K + 1];

        int answer = 0;
        for(int step=1; step <= K; step++) {

            int product = products[step];

            if(!visit[product]) {
                if(pick < N) {
                    pick++;
                    visit[product] = true;
                }
                else {
                    PriorityQueue<int []> pq = new PriorityQueue<>(new Comparator<int[]>() {
                        @Override
                        public int compare(int[] o1, int[] o2) {
                            return (o2[1] - o1[1]);
                        }
                    });

                    boolean [] selected = new boolean[K + 1];
                    for(int next=step + 1; next<=K; next++) {
                        if (visit[products[next]] && !selected[products[next]]) {
                            selected[products[next]] = true;
                            pq.add(new int[]{products[next], next});
                        }
                    }
                    for(int item=1; item <=K; item++) {
                        if(visit[item] == true && !selected[item]) {
                            pq.add(new int[]{item, 101});
                        }
                    }

                    int select = pq.peek()[0];
                    visit[select] = false;
                    visit[product] = true;
                    answer++;
                }
            }
        }

        System.out.println(answer);

    }
}
