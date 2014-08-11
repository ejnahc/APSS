# -*- coding: utf-8 -*-

from random import randint
import itertools
CASES = 40
print CASES
small = lambda: (randint(2,6), randint(2,6))
med = lambda: (randint(6,8), randint(6,8))
large = lambda: (randint(9,12), randint(9,12))
funcs = itertools.cycle([small, med, large])
for cc, f in zip(range(CASES), funcs):
    h, w = f()
    board = [["#"] * w for i in range(h)]
    put = 0
    for i in range(1000):
        if put >= 16: break
        y, x = randint(0, h-2), randint(0, w-2)
        coords = [(0,0),(0,1),(1,0),(1,1)]
        coords[randint(0,3)] = coords[-1]
        coords.pop()
        ok = True
        for dy, dx in coords:
            if board[y+dy][x+dx] == '.':
                ok = False
        if ok:
            for dy, dx in coords:
                board[y+dy][x+dx] = '.'
            put += 1
    print h, w
    print "\n".join(["".join(row) for row in board])

