# Ellie Kozlowski
# Alphabetty python solution
# 4/17/19

t = int(input())

# loop thorugh queries
for i in range(t):
    n = int(input())
    arr = []

    # read in input
    for j in range(n):
        arr.append(input())

    # varible to keep track of min
    min = 17
    

    # loop through all possible subsets
    for j in range(1, 2**n):
        # get bitmask of jth subset
        x = '{0:b}'.format(j)
        x = x.zfill(n)

        # variable to keep track of size of subset
        cnt = 0

        # boolean array to keep track of letters included in subset
        alpha = []
        for k in range(26):
            alpha.append(False)

        # iterate through bitmask
        for k in range(n):
            # check if kth bit is on
            if x[k] == '1':
                # increase count
                cnt += 1
                # iterate through length of arr[k]
                for l in range(len(arr[k])):
                    # check if arr[k][l] is a letter
                    if arr[k][l].isalpha():
                        # set idx of alpha to true
                        idx = ord(arr[k][l].lower()) - ord("a")
                        alpha[idx] = True

        # check if subset contains all letters
        good = True;
        for k in range(26):
            if alpha[k] == False:
                good = False
                break

        # check if it is the minimum subset
        if good:
            if min > cnt:
                min = cnt

    # check if no such subset exists
    if min == 17:
        min = -1

    print("Judge List #",(i + 1),": ",min, sep='')
