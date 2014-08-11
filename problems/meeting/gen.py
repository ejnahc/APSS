# -*- coding: utf-8 -*-

from random import *

def random_interval(): return sorted(sample(xrange(43200), 2))

MAXN = 20

def generate_random():
    n = randint(1,MAXN)
    return [(random_interval(), random_interval()) for i in xrange(n)]

def generate_possible():
    n = randint(1,MAXN)
    endpoints = sample(xrange(43200), randint(n,2*n+1))
    while len(endpoints) < 2*n:
        endpoints.append(endpoints[randint(0,len(endpoints)-1)])
    endpoints = sorted(endpoints)
    ret = []
    for i in xrange(n):
        pair1 = endpoints[2*i], endpoints[2*i+1]
        pair2 = random_interval()
        if randint(0,1) == 0: pair1, pair2 = pair2, pair1
        ret.append((pair1, pair2))
    return ret

def prnt(times):
    print len(times)
    for a, b in sorted(times):
        print "%d %d %d %d" % (a[0], a[1], b[0], b[1])

cases = 50
print cases
for cc in xrange(cases):
    if randint(0,2) == 0:
        prnt(generate_random())
    else:
        prnt(generate_possible())
