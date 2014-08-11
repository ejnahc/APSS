# -*- coding: utf-8 -*-
from math import sqrt
from random import randint
print 50
for cc in range(50):
    n = randint(1,5) * 2
    if randint(1,2) == 1:
        m = randint(1,n*n*int(sqrt(n)))
    else:
        m = n*n
    friends = [[False] * n for i in range(n)]
    for i in range(m):
        a, b = randint(0,n-1), randint(0,n-1)
        if a == b: continue
        friends[a][b], friends[b][a] = True, True
    rel = []
    for i in range(n):
        for j in range(i+1,n):
            if friends[i][j]:
                rel.append((i, j))
    print n, len(rel)
    print " ".join(["%d %d" % tup for tup in rel])


