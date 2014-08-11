#!/usr/bin/python
# -*- coding: utf-8 -*-

from random import random

names = ["small", "medium", "large", "xlarge"]
Ns = [12, 16, 20, 24]
cc = 20
for no, n, name in zip(range(len(Ns)), Ns, names):
    fp = open("input%.2d%s.txt" % (n, name), "w")
    fp.write("%d\n" % cc)
    for case in xrange(cc):
        fp.write("%d\n" % n);
        for i in xrange(n):
            fp.write("%.10lf %.10lf\n" % (random() * 1000, random() * 1000))
    fp.close()
