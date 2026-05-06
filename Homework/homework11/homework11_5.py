import math
n = int(input())
if int(math.sqrt(n)) * int(math.sqrt(n)) == n:
    a = int(math.sqrt(n))
    min_c = 2 * (a + n // a)
else:
    a = int(math.sqrt(n))
    while a >= 1:
        if (n % a != 0):
            a -= 1
            continue
        min_c = 2 * (a + n // a)
        break
print(min_c)