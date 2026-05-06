a, b, op = input().split(' ')
ops = ['+', '-', '*', '/']
if op not in ops:
    print("Invalid operator!")
else:
    if op == '+':
        print(int(a) + int(b))
    elif op == '-':
        print(int(a) - int(b))
    elif op == '*':
        print(int(a) * int(b))
    else:
        if (int(b) == 0):
            print("Divided by zero!")
        else:
            print(int(a) // int(b))