import java.util.*;

class Solution {
    
    static int [][] board;
    static final int inf = (int) 1e9;
    
    public int[] solution(int m, int n, int h, int w, int[][] drops) {
        
        board = new int[m][n];
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                board[i][j] = inf;
            }
        }
        for(int i = 0; i < drops.length; i++) {
            board[drops[i][0]][drops[i][1]] = i + 1;
        }
        
        
        int [][] minR = new int[m][n];
        
        for(int i = 0; i < m; i++) {
            Deque<Integer> dq = new LinkedList<>();
            for(int j = 0; j < n; j++) {
                while(!dq.isEmpty() && board[i][dq.peekLast()] >= board[i][j]) dq.removeLast();
                dq.addLast(j);
                
                if(dq.peekFirst() < j - w + 1)
                    dq.removeFirst();                
                
                if(0 <= j - w + 1) minR[i][j - w + 1] = board[i][dq.peekFirst()];
            }
        }
        
        int best = -1;
        int [] ans = new int[2];
        for(int i = 0; i < n; i++) {
            Deque<Integer> dq = new LinkedList<>();
            for(int j = 0; j < m; j++) {
                while(!dq.isEmpty() && minR[dq.peekLast()][i] >= minR[j][i])
                    dq.removeLast();
                dq.addLast(j);
                
                if(dq.peekFirst() < j - h + 1)
                    dq.removeFirst();                
                
                if(0 <= j - h + 1) {
                    int value = minR[dq.peekFirst()][i];
                    
                    if (best < value || (best == value && (j - h + 1 < ans[0] || (j - h + 1 == ans[0] && i < ans[1])))) {
                        best = value;
                        ans[0] = j - h + 1;
                        ans[1] = i;
                    }                    
                }
            }
        }
        
        return ans;
    }
}