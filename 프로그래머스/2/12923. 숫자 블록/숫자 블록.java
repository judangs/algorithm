class Solution {
    
    int count(long number) {
        
        if (number == 1) return 0;
        
        int ret = 1; // 기본값
        
        for (long i = 2; i * i <= number; i++) {
            
            if (number % i == 0) {
                
                long pair = number / i;
                
                // 더 큰 약수가 조건 만족하면 바로 반환
                if (pair <= 10000000) {
                    return (int) pair;
                }
                
                // 아니라면 작은 약수 후보 저장
                if (i <= 10000000) {
                    ret = (int) i;
                }
            }
        }
        
        return ret;
    }
    
    public int[] solution(long begin, long end) {
        
        int[] ans = new int[(int)(end - begin + 1)];
        
        for (int i = 0; i < ans.length; i++) {
            long now = begin + i;
            ans[i] = count(now);
        }
        
        return ans;
    }
}