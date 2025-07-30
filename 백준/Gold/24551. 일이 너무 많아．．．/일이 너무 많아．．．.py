import math

def gcd(a, b):
    while b:
        a, b = b, a % b
    return a

def counting(choice, num, pick, ptr, arr, N):
    if choice == pick:
        return N // num
    
    ret = 0
    for idx in range(ptr, len(arr)):
        ret += counting(choice + 1, num * arr[idx] // gcd(num, arr[idx]), pick, idx + 1, arr, N)
    
    return ret

def main():
    N = int(input())
    
    answer = 0
    arr = [11, 111, 11111, 1111111, 11111111111, 1111111111111, 11111111111111111]
    
    for pick in range(1, len(arr) + 1):
        if pick % 2 == 0:
            answer -= counting(0, 1, pick, 0, arr, N)
        else:
            answer += counting(0, 1, pick, 0, arr, N)
    
    print(answer)

if __name__ == "__main__":
    main()