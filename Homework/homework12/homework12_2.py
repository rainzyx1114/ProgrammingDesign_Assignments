import sys
def mysort(x):
    k = x[1:]
    if k == '2':
        k = 150
    elif k == 'A':
        k = 140
    elif k == 'K':
        k = 130
    elif k == 'Q':
        k = 120
    elif k == 'J':
        k = 110
    else:
        k = int(k) * 10
    if x[0] == 'h':
        k += 4
    elif x[0] == 's':
        k += 3
    elif x[0] == 'd':
        k += 2
    else:
        k += 1
    return k
for line in sys.stdin:
    cards = line.split()
    cards.sort(key=mysort, reverse=True)
    print(' '.join(cards))