t = int(input())
for i in range(t):
	vals = input().split(' ')
	a = int(vals[0])
	b = int(vals[1])
	c = int(vals[2])
	ans = a*a*a+b*b*b+c*c*c
	print(str(ans))
