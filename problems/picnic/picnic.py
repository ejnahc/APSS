# -*- coding: utf-8 -*-
import sys
rl = lambda: sys.stdin.readline().strip()
cases = int(rl())

global n, rel, cache

def solve(taken):
    if taken == (2**n)-1: return 1
    if taken in cache: return cache[taken]
    ret = 0
    for i in range(n):
        if (taken & (2**i)) == 0:
            for j in range(i+1, n):
                if rel[i][j] and (taken & (2**j)) == 0:
                    ret += solve(taken + (2**i) + (2**j))
            break
    cache[taken] = ret
    return ret

for cc in range(cases):
    n, m = map(int, rl().split())
    rel = [[False] * n for i in range(n)]
    pairs = map(int, rl().split())
    for i in range(m):
        a, b = pairs[i*2], pairs[i*2+1]
        rel[a][b], rel[b][a] = True, True
    cache = {}
    print solve(0)
