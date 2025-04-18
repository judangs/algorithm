import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class Main {

    static int N, M, K, P;
    static int INF = 1000000;

    private static int check(int [] position, int length) {
        int refery = 1, prev = position[0];
        for(int idx=1; idx<K; idx++) {
            int distance = position[idx] - prev;
            if(length <= distance) {
                refery++;
                prev = position[idx];
            }
        }


        return refery;
    }

    private static String batch(int [] position, int length) {

        int [] answer = new int[K];
        int refery = 1, prev = position[0];
        answer[0] = 1;
        for(int idx=1; idx<K; idx++) {
            int distance = position[idx] - prev;
            if(length <= distance) {
                answer[idx] = 1;
                prev = position[idx];
                if(++refery == M) break;
            }
        }

        String ret = "";
        for(int ans: answer) ret += ans;

        return ret;
    }

    public static void main(String[] args) throws Exception {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());

        int [] position = new int[K];
        st = new StringTokenizer(br.readLine());
        for(int idx=0; idx<K; idx++) {
            position[idx] = Integer.parseInt(st.nextToken());
        }

        int left = 0, right = INF + 1;
        while(left + 1 < right) {

            int mid = (left + right) / 2;
            if(check(position, mid) >= M) {
                left = mid;
            }
            else {
                right = mid;
            }
        }

        int answer = 0;
        if(check(position, right) == M) answer = right;
        else answer = left;

        System.out.println(batch(position, answer));
    }
}
