# a test implementation of boosted decision stumps: jongman@gmail.com
# run in ipython: %run -i play.py

import pylab
from pylab import *
from itertools import izip
import sys

x, y, label = array([]), array([]), array([], dtype=int16)

def onclick(event):
    global x, y, label
    x = append(x, event.xdata)
    y = append(y, event.ydata)
    label = append(label, 1 if event.button == 1 else -1)
    show()

def save():
    return (x, y, label)

def load(rep):
    global x, y, label
    x, y, label = rep
    show()

def graham_scan(x, y):

    # positive if (p1,p2) to (p1,p3) is a counterclockwise turn
    def ccw(p1, p2, p3):
        return (p2[1] - p1[1])*(p3[0] - p1[0]) - (p2[0] - p1[0])*(p3[1] -
                p1[1])
    assert ccw((0,0), (0,1), (1,1)) > 0
    assert ccw((0,0), (1,0), (1,1)) < 0
    def angle_compare(a, b):
        c = ccw(pivot, a, b)
        return -1 if c > 0 else 1

    pivot = (0,0)
    assert angle_compare((0,1), (1,1)) == -1
    assert angle_compare((1,0), (1,1)) == 1

    p = zip(y, x)
    p.sort()
    pivot = p[0]
    q = p[1:]
    q.sort(cmp=angle_compare)
    p = [pivot] + q

    n = len(p)
    p.append(p[0])
    m = 2
    for i in xrange(2,n):
        while m >= 2 and ccw(p[m-2], p[m-1], p[i]) <= 0:
            m -= 1
        p[m] = p[i]
        m += 1
    return p[:m]

def line_intersect(a, b, c, d):
    a1 = b[0] - a[0]
    b1 = a[1] - b[1]
    c1 = a[0] * (b[1] - a[1]) - a[1] * (b[0] - a[0])

    a2 = d[0] - c[0]
    b2 = c[1] - d[1]
    c2 = c[0] * (d[1] - c[1]) - c[1] * (d[0] - c[0])

    if fabs(a1*b2 - a2*b1) < 1e-8: return None
    y = (c2*a1-c1*a2) / (a2*b1-a1*b2)
    x = (c2*b1-c1*b2) / (a1*b2-a2*b1)
    return y, x

def between(a, b, c):
    return a-1e9 <= b <= c+1e-9 or c-1e9 <= b <= a+1e9
def on_segment(a, b, p):
    return between(a[0], p[0], b[0]) and between(a[1], p[1], b[1])


def intersect(a, b, c, d):
    p = line_intersect(a,b,c,d)
    if not p: return p
    if not on_segment(a,b,p) or not on_segment(c,d,p): return None
    return p

def decompose(hull1, hull2):
    upper, lower = [], []
    for h in [hull1, hull2]:
        for i in xrange(len(h)-1):
            if h[i][1] <= h[i+1][1]:
                lower.append((h[i], h[i+1]))
            else:
                upper.append((h[i], h[i+1]))
    return upper, lower

def span(x): return x[1] - x[0]
def get_at(segments, x):
    return [seg[0][0] + (seg[1][0] - seg[0][0]) * (x - seg[0][1]) /
            (seg[1][1] - seg[0][1]) for seg in segments
            if between(seg[0][1], x, seg[1][1])]
def f(lower, upper, x):
    return max(get_at(lower, x)), min(get_at(upper, x))

def solve(hull1, hull2):

    upper, lower = decompose(hull1, hull2)
    for i in xrange(-1,len(hull1)-1):
        for j in xrange(-1,len(hull2)-1):
            p = intersect(hull1[i], hull1[i+1], hull2[j], hull2[j+1])
            if p:
                print "Two hulls intersect at (%g,%g)" % p


    lo = max(min([h[1] for h in hull1]), min([h[1] for h in hull2]))
    hi = min(max([h[1] for h in hull1]), max([h[1] for h in hull2]))

    for iter in xrange(200):
        aab = (lo+lo+hi)/3.
        abb = (lo+hi+hi)/3.
        if span(f(lower, upper, aab)) < span(f(lower, upper, abb)):
            lo = aab
        else:
            hi = abb
    ys = f(lower, upper, hi)
    plot([hi, hi], [ys[0], ys[1]], 'k--', lw=2)
    print hi, ys

def show():
    global pred
    grid(True)
    fig.axes[0].collections = []
    fig.axes[0].lines = []

    pos = where(label == 1)
    neg = where(label == -1)
    global poshull, neghull
    poshull, neghull = None, None
    if len(pos[0]) > 0:
        poshull = graham_scan(x[pos], y[pos])
        poshull.append(poshull[0])
        plot([h[1] for h in poshull], [h[0] for h in poshull], "-",
            color="0.4")
    if len(neg[0]) > 0:
        neghull = graham_scan(x[neg], y[neg])
        neghull.append(neghull[0])
        plot([h[1] for h in neghull], [h[0] for h in neghull], "-",
            color="0.4")
    if len(pos[0]) > 0:
        scatter(x[pos], y[pos], s=80, marker="o", facecolor="0.1",
                linewidth=0, label="Flower A",zorder=2)

    if len(neg[0]) > 0:
        scatter(x[neg], y[neg], s=120, marker="x", edgecolor="0.1",
                linewidth=3, label="Flower B",zorder=3)

    if poshull and neghull:
        solve(poshull, neghull)
    sys.stdout.flush()

    xlim((0, 100))
    ylim((0, 100))
    subplots_adjust(0.1,0.1,0.9,0.9)
    legend()
    gca().set_aspect("equal")
    pylab.show()

if __name__ == "__main__":
    global fig
    close()
    if "cb" in globals():
        del cb
    fig = figure()
    cid = fig.canvas.mpl_connect('button_press_event', onclick)
    show()

    #set_cmap()

