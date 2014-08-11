#!/usr/bin/python
import sys
cache = {}
TM = 10 * 1000 * 1000
def solve(blocks, lastlevel):
    if blocks == 0: return 1
    if (blocks, lastlevel) in cache: return cache[(blocks, lastlevel)]
    ret = 0
    for size in range(1, blocks+1):
        if lastlevel == 0:
            ret = (ret + solve(blocks - size, size)) % TM
        else:
            ret = (ret + solve(blocks - size, size) * (lastlevel + size - 1)) % TM
    cache[(blocks, lastlevel)] = ret
    return ret
tests = map(int," ".join(sys.stdin.readlines()).split()[1:])
for i in range(len(tests)):
    print solve(tests[i], 0)

