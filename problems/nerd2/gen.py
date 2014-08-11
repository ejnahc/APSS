# -*- coding: utf-8 -*-
from random import *

Ns = ([10,20,30,40,50,60,70,80,90,100] + [100]*10 + [200]*10 +
        [10000,20000,30000,40000,50000]*4)
print len(Ns)
for i, N in enumerate(Ns):
    print N
    if i % 2 == 0:
        x = sample(xrange(100000), N)
        y = sample(xrange(100000), N)
    else:
        x = range(N)
        y = range(N)
        if randint(0,1) == 0: x = list(reversed(x))
        if randint(0,1) == 0: y = list(reversed(y))
        if randint(0,1) == 0: x,y=y,x
    for xx,yy in zip(x,y):
        print xx, yy
