# -*- coding: utf-8 -*-

import copy
import random

init = [[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,0]]
dx = [1, -1, 0, 0]
dy = [0, 0, 1, -1]

N = 1000
print N
for cc in xrange(1,N+1):
    state = copy.deepcopy(init)
    by = bx = 3
    for i in xrange(100+cc/10):
        while True:
            k = random.choice([0,1,2,3])
            ny, nx = by + dy[k], bx + dx[k]
            if 0 <= ny < 4 and 0 <= nx < 4:
                state[ny][nx], state[by][bx] = state[by][bx], state[ny][nx]
                by, bx = ny, nx
                break
    for i in xrange(4):
        print " ".join(map(str, state[i]))
