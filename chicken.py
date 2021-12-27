# Solution to Atharva and Chicken
# by Jacob Magnuson

# Read number of testcases
T = int(input())

for t in range(T):
    # Read total number of days, skip days, and pickle probability
    inp = input().split()
    n, d, p = int(inp[0]), int(inp[1]), float(inp[2])

    '''
    We'll solve this problem with dynamic programming. In the array memo below,
    memo[x] will correspond to the answer if the semester is x days long.

    If there are x days left in the semester, and Atharva gets pickles, he won't
    return until there are x - d days left in the semester (unless there are
    fewer than d days remaining, in which case he won't return at all). If he
    doesn't get pickles, he will return when there are x - 1 days left. We can
    then compute his expected number of pickles by using the expected number on
    those two other days (x - d and x - 1) as well as the expected number of
    pickles he gets on day x specifically.

    When Atharva gets pickles, he equiprobably gets 1, 2, or 3 pickles, so he
    can expect to get the average (2) when he does get pickles. Furthermore, if
    Atharva gets pickles with probability p, he doesn't get them with
    probability (1 - p). Putting this all together, we can compute the expected
    number of pickles he gets on day x as follows:

        memo[x] = p * (2 + memo[x - d])     +   (1 - p) * (memo[x - 1])

    With probability p, he gets (an expected) 2 pickles, and returns when the
    semester has x - d days remaining. With probability (1 - p), he gets no
    pickles, and returns when there is 1 day remaining.
    '''
    memo = [0]
    for x in range(1, n + 1):
        skip = 0 if x <= d else memo[x - d]
        memo.append(p * (2 + skip) + (1 - p) * memo[-1])

    print(memo[-1])
