t = int(input())
for i in range(t):
	inp = input().split(' ')
	n = int(inp[0])
	a = int(inp[1])
	b = int(inp[2])
	
	if (b < a):
		temp = b
		b = a
		a = temp
	
	if (n % 2 == 0):
		if (a % 2 != b % 2):
			print('Graph #'+str(i+1)+': Impossible')
		else:
			option1 = (b-a)//2
			option2 = (a+n-b)//2
			print('Graph #'+str(i+1)+': '+str(int(min(option1, option2))))
	else:
		ans = 0;
		if (a % 2 != b % 2):
			ans = (a+n-b)//2
		else:
			ans = (b-a)//2
		print('Graph #'+str(i+1)+': '+str(int(ans)))
