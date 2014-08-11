#!/usr/bin/python
# -*- coding: utf-8 -*-

from random import *
colors = 'bw'
splits = 200
def generate(depth):
    global splits
    if depth >= 20 or splits == 0 or randint(1,10) <= 2: return choice(colors)
    splits -= 1
    return "x" + "".join([generate(depth+1) for i in range(4)])

print 50
for cc in range(50):
    splits = 200
    rep = generate(0)
    assert len(rep) <= 1000, len(rep)
    print rep

