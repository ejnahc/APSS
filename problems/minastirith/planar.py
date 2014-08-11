# -*- coding: utf-8 -*-

from common import *
def sched(y, x1, x2, lw=1, ls='-'):
    x2 -= 0.1
    line(y, x1, y, x2, '#444444', ls=ls, lw=lw)
    line(y+0.1, x1, y-0.1, x1, '#444444', lw=lw)
    line(y+0.1, x2, y-0.1, x2, '#444444', lw=lw)

schedules1 = [(1, 7), (2, 4), (6, 9), (3, 5), (9, 10),
        (1, 4), (2, 7), (2, 4), (8, 10), (8, 9), (5, 9)]

schedules = schedules1

layers = []
for begin, end in schedules:
    found = False
    for layer in layers:
        intersect = False
        for obegin, oend in layer:
            if not (end <= obegin) and not (oend <= begin):
                intersect = True
        if not intersect:
            layer.append((begin, end))
            found = True
            break
    if not found:
        layers.append([(begin, end)])

full()
for y in xrange(len(layers)):
    for begin, end in layers[y]:
        sched(y, begin, end, ls='--')
sched(-1, 2.4, 9.5, lw=3)
xlim(0.5,10.5)
ylim(-1.5,len(layers)-0.5)
yticks([])
show()
