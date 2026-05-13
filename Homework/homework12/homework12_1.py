n, m = input().split()
n, m = int(n), int(m)
arr = []
for i in range(n):
    row = input().split()
    arr.extend(row)
arr_trans = [arr[j * m + i] for i in range(m) for j in range(n)]
for i in range(m):
    for j in range(n):
        print(arr_trans[i * n + j], end=' ')
    print('')