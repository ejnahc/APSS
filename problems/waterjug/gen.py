# -*- coding: utf-8 -*-

from random import randint
from fractions import gcd

MAX_JUGS, MAX_CAPA = 6, 30
CASES = 100
print CASES
for cc in xrange(CASES):
    n = randint(2, MAX_JUGS)
    caps = [randint(1,MAX_CAPA) for i in xrange(n)]
    g = reduce(gcd, caps)
    while True:
        target = randint(1, max(caps))
        if target % g == 0: break
    print n, target
    print " ".join(map(str, caps))
