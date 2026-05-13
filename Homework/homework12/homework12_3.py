n, m = map(int, input().split())
dict = {}
for _ in range(m):
    name, price, num = input().split()
    dict[name] = [int(price), int(num)]
profit = 0
for _ in range(n):
    names = input().split()
    for i in range(3):
        name = names[i]
        if dict[name][1] > 0:
            profit += dict[name][0]
            dict[name][1] -= 1
print(profit)