#!/usr/bin/python
# -*- coding: utf-8 -*-
import sys, random

def solve(h):
    # base case
    n = len(h)
    if n == 1: return h[0]

    # split into 2
    half = n / 2
    ret = max(solve(h[:half]), solve(h[half:]))

    left, right = half-1, half
    height = min(h[left], h[right])
    while True:
        ret = max(ret, height * (right-left+1))
        if left == 0 and right == n-1: break
        if right < n-1 and (left == 0 or h[left-1] < h[right+1]):
            right += 1
            height = min(height, h[right])
        else:
            left -= 1
            height = min(height, h[left])
    return ret

# inp = open("histo.in", "w")
# outp = open("histo.out", "w")
# 
# inp.write("50\n")
# ns = [5, 10, 100, 1000, 5000, 10000, 15000, 20000, 20000]
# ranges = [(0,10000), (9999,10000), (5000,10000), (0,1)]
# for cc in xrange(50):
#     n = ns[cc % len(ns)]
#     lo, hi = ranges[cc % (len(ranges))]
#     h = [random.randint(lo, hi) for i in xrange(n)]
#     inp.write("%d\n%s\n" % (n, " ".join(map(str,h))))
#     outp.write("%d\n" % solve(h))
# 
# """


rl = lambda: sys.stdin.readline().strip()
cc = int(rl())
for c in xrange(cc):
    rl()
    h = map(int, rl().split())
    print solve(h)
