N = int(input())

mod = 1_000_000_007

answer = 0
while(0 < N):
    x, K = map(int, input().split(' '))
    
    binary = ""
    while(0 < K):
        if K % 2 == 0 :
            binary += '0'
        else:
            binary += '1'

        K //= 2

    p = 1
    for i in range(len(binary)):
        if binary[i] == '1':
             answer += p
        p *= x

    N -= 1

print(answer % mod)