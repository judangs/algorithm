import java.util.*;

public class Main {

    static int N;

    public static void main(String[] args) throws Exception {

        Scanner sc = new Scanner(System.in);

        N = sc.nextInt();

        int [] current = new int[N];
        int [] target = new int[N];
        for(int idx=0; idx<N; idx++) current[idx] = sc.nextInt();
        for(int idx=0; idx<N; idx++) target[idx] = sc.nextInt();

        int [] diff = new int[N];
        for(int idx=0; idx<N; idx++) {
            diff[idx] = target[idx] - current[idx];
        }

        int answer = 0;
        for(int left=0; left<N; left++) {
            while(diff[left] != 0) {
                if(diff[left] > 0) {
                    int right = left;
                    while(right < N && diff[right] > 0) {
                        right++;
                    }

                    right = Math.min(right - 1, N - 1);

                    int count = 81;
                    for(int idx=left; idx<=right; idx++) {
                        count = Math.min(count, Math.abs(diff[idx]));
                    }

                    for(int idx=left; idx<=right; idx++) {
                        diff[idx] -= count;
                    }
                    
                    answer += count;
                }
                else if(diff[left] < 0) {
                    int right = left;
                    while(right < N && diff[right] < 0) {
                        right++;
                    }

                    right = Math.min(right - 1, N - 1);

                    int count = 81;
                    for(int idx=left; idx<=right; idx++) {
                        count = Math.min(count, Math.abs(diff[idx]));
                    }

                    for(int idx=left; idx<=right; idx++) {
                        diff[idx] += count;
                    }
                    
                    answer += count;
                }
            }
        }


        System.out.println(answer);
    }
}
