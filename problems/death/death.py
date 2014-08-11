# -*- coding: utf-8 -*-
import sys
import numpy as np
rl = lambda: sys.stdin.readline().strip()
cases = int(rl())

for cc in xrange(cases):
    n, x, m, t = map(int, rl().split())
    pointed = map(int, rl().split())
    mat = np.zeros((n,n))
    mat[pointed[0]-1][0] = 1.0
    for i in xrange(1,n):
        for delta in xrange(-t,t+1):
            mat[(pointed[i]-1+delta)%n][i] = 1.0 / (2 * t + 1)
    mat = np.linalg.matrix_power(mat, x)
    for q in map(int, rl().split()):
        print "%.8lf " % mat[q-1][0],
    print


