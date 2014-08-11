#!/usr/bin/python
# -*- coding: utf-8 -*-

import argparse, random

deltas = [(0,1), (0,-1), (1,0), (-1,0)]

def shuffled(seq):
    s = list(seq)
    random.shuffle(s)
    return s

def put(cells, y, x):
    n = len(cells)
    if y < 1 or x < 1 or y >= n or x >= n: return
    if cells[y][x] > 0: return
    for d in shuffled(xrange(1,10)):
        ok = True
        for dy, dx in deltas:
            cy, cx = y+dy, x+dx
            while 0 <= cy < n and 0 <= cx < n:
                if cells[cy][cx] == d:
                    ok = False
                    break
                cy += dy
                cx += dx
            if not ok: break
        if ok:
            cells[y][x] = d
            break
    if cells[y][x] != 0:
        for dy, dx in shuffled(deltas):
            put(cells, y+dy, x+dx)

def gen_grids(args):
    n = random.randint(args.min_n, args.max_n)
    cells = [[0] * n for i in xrange(n)]
    coords = [(i,j) for i in xrange(1,n) for j in xrange(1,n)]
    for y, x in shuffled(coords):
        put(cells, y, x)
    return cells

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--cases", type=int, default=50)
    parser.add_argument("--min-n", type=int, default=10)
    parser.add_argument("--max-n", type=int, default=20)
    parser.add_argument("--min-white-cells", type=int, default=50)

    args = parser.parse_args()

    print args.cases
    for cc in xrange(args.cases):
        grid = gen_grids(args)
        print len(grid)
        for row in grid: print " ".join(map(str, row))

if __name__ == "__main__":
    main()
