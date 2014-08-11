# -*- coding: utf-8 -*-

from common import *

def plot1():
    points = [(72,50),(57,67),(74,55),(64,60)]

    minx = min([x[0] for x in points])
    maxx = max([x[0] for x in points])
    miny = min([x[1] for x in points])
    maxy = max([x[1] for x in points])
    n = len(points)
    clf()
    for i in xrange(n):
        subplot(2,2,i+1)
        title("(%s)" % chr(ord('a') + i))
        gca().set_aspect("equal")
        p = points[:i+1]

        dom, not_dom = [], []
        for a in xrange(i+1):
            dominated = False
            for b in xrange(i+1):
                if p[a][0] < p[b][0] and p[a][1] < p[b][1]:
                    dominated = True
            (dom if dominated else not_dom).append(p[a])
        if dom:
            plot([x[0] for x in dom], [x[1] for x in dom], 'kx', ms=12, mew=4)
        if not_dom:
            plot([x[0] for x in not_dom], [x[1] for x in not_dom], 'ko', ms=12,
                    mfc='white', mew=4)
            for x, y in not_dom:
                box(0, 0, y, x, fill=True, fc="0.8", lw=0)
                line(y,x,y,0,"-",color="0.6")
                line(y,x,0,x,"-",color="0.6")
        xlim((minx-4,maxx+4))
        ylim((miny-4,maxy+4))
    subplots_adjust(0.05,0.05,0.95,0.95)
    show()

def plot2():
    points = [(60,89),(69,72),(84,66),(91,60)]
    queries = [(77,77), (66,62)]
    clf()
    enable_tex()
    plot([x[0] for x in queries], [x[1] for x in queries], 'k*', ms=12,
            mfc='white', mew=4)
    for i, (x, y) in enumerate(queries):
        text(x+1, y+1, "$q_{%d}$" % (i+1), size=18)
    plot([x[0] for x in points], [x[1] for x in points], 'ko', ms=12,
            mfc='white', mew=4)
    for i, (x, y) in enumerate(points):
        text(x+1, y+1, "$p_{%d}$" % (i+1), size=18)
        box(0, 0, y, x, fill=True, fc="0.8", lw=0)
        line(y,x,y,0,"-",color="0.6")
        line(y,x,0,x,"-",color="0.6")
    xlim((50,100))
    ylim((50,100))
    gca().set_aspect("equal")
    show()
plot2()



