#!/usr/bin/python
# -*- coding: utf-8 -*-

import argparse, random

def print_case(args):
    h = random.randint(1, args.maxboardsize)
    w = random.randint(1, args.maxboardsize)
    board = [[("." if random.randint(1, 100) > args.obstacles else "#")
        for j in xrange(w)] for i in xrange(h)]
    cells = set()
    cells.add((0,0))
    blocksize = random.randint(3, args.maxblocksize)
    directions = [(0,1),(0,-1),(1,0),(-1,0)]
    while len(cells) < blocksize:
        cell = random.choice(list(cells))
        dir = random.choice(directions)
        newcell = (cell[0] + dir[0], cell[1] + dir[1])
        cells.add(newcell)
    minX = min([c[1] for c in cells])
    minY = min([c[0] for c in cells])
    maxX = max([c[1] for c in cells])
    maxY = max([c[0] for c in cells])

    block = [[("." if (y,x) not in cells else "#")
        for x in xrange(minX,maxX+1)]
        for y in xrange(minY,maxY+1)]
    print h, w, maxY-minY+1, maxX-minX+1
    for row in board: print "".join(row)
    for row in block: print "".join(row)
    #print cells

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--cases", default=50, type=int)
    parser.add_argument("--maxboardsize", default=8, type=int)
    parser.add_argument("--maxblocksize", default=6, type=int)
    parser.add_argument("--obstacles", default=30, type=int)
    args = parser.parse_args()

    print args.cases
    for case in xrange(args.cases):
        print_case(args)

if __name__ == "__main__":
    main()
