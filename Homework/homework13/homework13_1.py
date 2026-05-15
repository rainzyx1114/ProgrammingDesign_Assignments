def recover(s):
    if (len(s) <= 1):
        return s
    center = s[0]
    length = len(s) - 1
    l = s[1 : 1 + (length // 2)]
    r = s[1 + (length // 2) :]
    return recover(l) + center + recover(r)
s = input()
print(recover(s))