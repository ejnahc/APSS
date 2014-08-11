# -*- coding: utf-8 -*-
from pylab import *
from random import *

cases = 100
max_n = 8

inp = open("poly.in", "w")
outp = open("poly.out", "w")
inp.write("%d\n" % cases)
for cc in xrange(cases):
    n = randint(2,max_n)
    xs = array([(random()-0.5)*10 for i in xrange(n)])*(random()+1)
    coefs = poly(xs)
    inp.write("%d\n%s\n" % (n, " ".join(["%.12lf" % c for c in reversed(coefs)])))
    outp.write("%s\n" % " ".join(["%.12lf" % s for s in sorted(xs)]))

