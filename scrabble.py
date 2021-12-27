# solution to: Super Scrabble for HSPT Online 2019
# author: John Edwards 2019-04-19

import sys
sys.setrecursionlimit(100001)

is_word = '_end_'
def make_trie(lexicon):
    root = dict()
    for word in lexicon:
        node = root
        for letter in word:
            node = node.setdefault(letter, {})
        node[is_word] = is_word
    return root

# dfs down the trie
def dfs(p, node, letters):
    # if the word that has been placed down is valid
    # then player p loses, so return 1-p
    if is_word in node:
        return 1-p

    # set flags to False
    win = False
    draw = False
    # try placing every valid letter
    for c in letters:
        # if this letter is part of a word
        # then dfs from that node as the other player
        if c in node:
            # recurse down this path of the trie
            sub = dfs(1-p, node[c], letters)
            # does choosing the letter cause you to win?
            if sub == p:
                win = True
            # if you don't win, do you draw?
            elif sub == 2:
                draw = True
        # if this letter makes an invalid word
        # then placing it forces a draw
        else:
            draw = True
    
    # if any letter choice forced you to win you win
    if win:
        return p
    # otherwise if you can force a draw return 2
    elif draw:
        return 2
    # otherwise you lose
    else:
        return 1-p

t = int(input())
for tt in range(1, t+1):
    n, m = map(int, input().split())
    letters = input()
    lexicon = []
    for i in range(m):
        lexicon.append(input())
    
    # make trie based off of lexicon
    trie = make_trie(lexicon)
    
    out = ["Alice wins", "Bob wins", "Draw"]
    print("Game #%d: %s" % (tt, out[dfs(0, trie, letters)]))