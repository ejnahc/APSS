# -*- coding: utf-8 -*-

from random import randint
import sys

MAX_DISCS = 14 if len(sys.argv) == 1 else int(sys.argv[1])

CASES = 50
Ns = [randint(1,MAX_DISCS) for i in xrange(CASES-5)] + [MAX_DISCS] * 5
print CASES
for n in Ns:
    print n
    tower = [[],[],[],range(n,0,-1)]
    for _ in xrange(100000):
        a, b = randint(0, 3), randint(0, 3)
        if a == b or not tower[a] or (tower[b] and tower[a][-1] > tower[b][-1]): 
            continue
        tower[b].append(tower[a].pop())
    for t in tower:
        print len(t), " ".join(map(str, t))

