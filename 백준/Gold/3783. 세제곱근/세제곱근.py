import math
from decimal import Decimal, getcontext, ROUND_DOWN

getcontext().prec = 1000

T = int(input())
for _ in range(T):
    num = input().strip()
    N = Decimal(num)
    
    lo = Decimal('1')
    hi = N
    for _ in range(1000):
        mid = Decimal(Decimal(lo + hi) / Decimal('2'))
        if(mid ** 3 < N):
            lo = mid
        else :
            hi = mid

    answer = hi
    answer = answer.quantize(Decimal('1.0000000000'), rounding=ROUND_DOWN)
    print(f"{answer:.10f}")