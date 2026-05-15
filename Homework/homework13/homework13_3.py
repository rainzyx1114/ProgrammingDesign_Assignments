class A:
    def __init__(self, x):
        self.x = x
    def __eq__(self, other):
        if isinstance(other, A):
            return self.x == other.x
    def __ge__(self, other):
        if isinstance(other, A):
            return self.x >= other.x
    def __lt__(self, other):
        if isinstance(other, A):
            return self.x < other.x
        if isinstance(other, int):
            return self.x < other


if __name__ == "__main__":
    a, b, c = map(int, input().split())
    print(isinstance(A(2), A))
    print(A(a) < A(b))
    print(A(a) >= A(c))
    print(A(a) < c)