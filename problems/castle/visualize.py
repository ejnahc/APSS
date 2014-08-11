# -*- coding: utf-8 -*-
from common import *

def plot1():
    clf()
    circles = [
            (15, 21, 20),
            (15, 15, 10), (12, 13, 5), (12, 12, 3),
            (19, 19, 2), (24, 30, 5),
            (10, 32, 7), (9, 32, 4),
            ]
    print len(circles)
    for i, (y, x, r) in enumerate(circles):
        print x, y, r
        text(x+r+0.1, y, str(i))
        circle(y, x, r, 'k', lw=2)
    hideticks()
    subplots_adjust(left=0.05,right=0.95,top=0.95,bottom=0.05)
    expand(0.05)
    gca().set_aspect("equal")
    show()

plot1()

