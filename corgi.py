# Solution to The Continuing Corgi Conundrum
# by Jacob Magnuson

import sys, math
sys.setrecursionlimit(1011) # default is set to 1000 :(

# Read number of testcases
T = int(input())

for t in range(T):
    # Read number of nodes and edges
    n, m, k = map(int, input().split())
    # Create adjacency list
    adj = [[] for i in range(n)]

    # Read in edges and populate adjacency list
    for i in range(m):
        u, v = map(lambda x: int(x) - 1, input().split())
        adj[u].append(v)
        adj[v].append(u)

    # DFS which returns the size of n's component
    def size(r):
        t, q, vis = 0, [r], [False] * n
        vis[r] = True
        while len(q) > 0:
            c = q.pop()
            t += 1
            for v in adj[c]:
                if not vis[v]:
                    vis[v] = True
                    q.append(v)
        return t

    # Store factorials and N choose K function
    fac = [math.factorial(i) for i in range(0, 1001)]
    choose = lambda n, k: fac[n] / (fac[k] * fac[n - k])


    # Store result
    res = 0

    '''
    Suppose Corgi X is a member of a connected friend network of size c.
    If any of those c Corgis are chosen, then Corgi X will be chosen as well.
    The probability that this Corgi goes home with Charles, then, is equal to
    the probability that Charles selects at least one corgi from this friend
    group. We'll use a common trick: this is equal to 1 minus the proability
    that a corgi from this friend group is NEVER chosen.

    There are (N choose K) ways to select K corgis from our total group of N.
    In order to not select a corgi from a group of size c, we must make one of
    the (N-c choose K) selections that do not have any corgi from that group.
    Since every different selection is equally likely, the probability that a
    corgi in a group of size c is not selected is:

        x = (N-c choose K) / (N choose K)

    And the probability it is, then, is (1 - x). By linearity of expectation,
    we can compute this individually for each corgi, and print the sum of the
    answers we find.

    For an extra challenge, how would you solve this problem for bounds of N
    up to 10**5?

    Extra note: If k > N - c, by the Pigeonhole Principle we will certainly
    choose one of these corgis in the size c group, so watch out for that.
    '''

    # save n choose k, the denominator of our fraction
    nck = choose(n, k)

    # For each corgi, get the size of its friend group, and perform the
    # computation described above.
    for r in range(n):
        c = size(r)
        if k > n - c: res += 1; continue # this corgi will certainly be chosen
        x = choose(n - c, k) / nck
        res += 1 - x

    # Print the answer!
    print("Pond #%d: %.3f" % (t + 1, res))
