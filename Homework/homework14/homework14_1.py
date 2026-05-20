def cons(x,y):
	def f(label):
		if label == 0:
			return x
		elif label == 1:
			return y
		else:
			return 'error'
	return f
s = input().split()
a,b = s[0],s[1]
pair = cons(a,b)
print(pair(int(input())))