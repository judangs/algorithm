import java.io.BufferedReader;
import java.io.InputStreamReader;

import java.util.*;

public class Main {

    static int N, K;
    static int INF = 987654321;
    static PriorityQueue<int []> plug = new PriorityQueue<>(new Comparator<int[]>() {
        @Override
        public int compare(int[] o1, int[] o2) {
            return o2[1] - o1[1];
        }
    });

    public static void main(String[] args) throws Exception {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());

        List<PriorityQueue<int[]>> item = new ArrayList<>();
        for(int idx=0; idx<=K; idx++) {
            item.add(new PriorityQueue<>(new Comparator<int[]>() {
                @Override
                public int compare(int[] o1, int[] o2) {
                    return o1[1] - o2[1];
                }
            }));
        }

        int [] products = new int[K];

        st = new StringTokenizer(br.readLine());
        for(int step=0; step<K; step++) {
            int product = Integer.parseInt(st.nextToken());
            products[step] = product;
            item.get(product).add(new int[]{product, step});
        }

        boolean [] visit = new boolean[K + 1];

        int answer = 0, count = 0;
        for(int step=0; step<K; step++) {
            int product = products[step];
            if(!visit[product]) {
                if(count++ < N) {
                    item.get(product).poll();
                    if(!item.get(product).isEmpty()) plug.add(new int[]{product, item.get(product).peek()[1]});
                    else plug.add(new int[]{product, INF});
                    visit[product] = true;
                }
                else {

                    int out = plug.poll()[0];
                    item.get(product).poll();

                    if(!item.get(product).isEmpty()) plug.add(new int[]{product, item.get(product).peek()[1]});
                    else plug.add(new int[]{product, INF});

                    visit[out] = false;
                    visit[product] = true;
                    answer++;
                }
            }
            else {
                // 현재 꼽혀있는 경우, idx 갱신을 위해 넣어주는 작업. 이전에 들어간 노드의 경우
                // 내림차순 정렬에 따라 마지막에 삽입되는 노드보다 항상 우선순위가 낮은 채로 유지
                item.get(product).poll();
                if(!item.get(product).isEmpty()) plug.add(new int[]{product, item.get(product).peek()[1]});
                else plug.add(new int[]{product, INF});
            }
        }

        System.out.println(answer);

    }
}
