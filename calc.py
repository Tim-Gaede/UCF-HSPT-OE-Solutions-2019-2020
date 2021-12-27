# takes a value in and performs button B's operation on it
def press(x, B):
    if B[0] == 'A':
        return x+B[1]
    if B[0] == 'S':
        return x-B[1]
    if B[0] == 'M':
        return x*B[1]
    if B[0] == 'D':
        if x % B[1] == 0:
            return int(x/B[1])
        else:
            return 100000000
    if B[0] == 'T':
        return int(str(x).replace(str(B[1]), str(B[2])))
    if B[0] == 'P':
        if x >= 0:
            return 10*x+B[1]
        return -(10*(-x)+B[1])

# checks whether the value is in the proper range
def valid(x):
    return -100000000 < x and x < 100000000

# read in input
v = int(input())
for vv in range(1, v+1):
    s, t, b, n = map(int, input().split())
    
    # create the buttons
    B = [[] for i in range(n)]
    for i in range(n):
        B[i] = input().split()
        for j in range(1, len(B[i])):
            B[i][j] = int(B[i][j])
    
    # keep track of what we see at each button press
    sets = [set() for i in range(b+1)]
    sets[0].add(s)
    
    # for each press try each button
    for i in range(b):
        for j in sets[i]:
            for k in range(n):
                res = press(j, B[k])
                if valid(res):
                    sets[i+1].add(res)
    
    # output the answer
    out = ["It can be done", "You should give up"]
    if t in sets[b]:
        print("Level #%d: %s" % (vv, out[0]))
    else:
        print("Level #%d: %s" % (vv, out[1]))
