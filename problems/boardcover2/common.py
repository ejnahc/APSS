# -*- coding: utf-8 -*-
from pylab import *
import matplotlib.patches as mpatches

def arc(y, x, r, t1, t2, *args, **kwargs):
    an = arange(t1,t2,0.001)
    plot(x + r * cos(an), y + r * sin(an), *args, **kwargs)

def sector(y, x, r, t1, t2, *args, **kwargs):
    arc(y, x, r, t1, t2, *args, **kwargs)
    plot([x+r*cos(t1), x, x+r*cos(t2)],
         [y+r*sin(t1), y, y+r*sin(t2)], *args, **kwargs)

def wedge(y, x, r, t1, t2, *args, **kwargs):
    gca().add_patch(mpatches.Wedge((x,y), r, t1/pi*180, t2/pi*180, *args,
        **kwargs))

def circle(y, x, r, *args, **kwargs):
    arc(y, x, r, 0, 2*pi, *args, **kwargs)

def box(y1, x1, y2, x2, *a, **k):
    bar(bottom=[y1], height=[y2-y1], left=[x1], width=[x2-x1], *a, **k)

def absmin(a, b):
    if a > 0: return min(a, b)
    return max(a,b)

def line(y1, x1, y2, x2, *args, **kwargs):
    xs, ys = [x1, x2], [y1, y2]
    if "split_at" in kwargs:
        split_at = kwargs["split_at"]
        del kwargs["split_at"]

        from math import hypot
        dist = hypot(y2-y1, x2-x1)
        markers = max(2, int(dist / split_at + 1))
        dx, dy = x2-x1, y2-y1
        xs = [x1+absmin(dx, dx*i/float(markers-1)) for i in range(markers)]
        ys = [y1+absmin(dy, dy*i/float(markers-1)) for i in range(markers)]
        print "(%g,%g) => (%g,%g) split_at %g markers %d: %s %s" % (y1, x1, y2, x2,
                split_at, markers, ys, xs)
    plot(xs, ys, *args, **kwargs)

def hideticks():
    xticks([])
    yticks([])

def arr(y1, x1, y2, x2, head_p=0.02, both_dir=False, *args, **kwargs):
    sz = hypot(y2-y1, x2-x1)
    if "head_length" not in kwargs:
        kwargs["head_length"] = sz*head_p
    if "head_width" not in kwargs:
        kwargs["head_width"] = sz*head_p
    if "head_sz" in kwargs:
        kwargs["head_length"] = kwargs["head_sz"]
        kwargs["head_width"] = kwargs["head_sz"]
        del kwargs["head_sz"]
    ratio = (1.0 - kwargs["head_length"] / hypot(x2-x1,y2-y1)) * 0.95
    arrow(x1, y1, (x2-x1)*ratio, (y2-y1)*ratio, *args,
            facecolor='k', **kwargs)

def full():
    clf()
    plt = gcf().add_subplot(111,frameon=False,xticks=[],yticks=[])
    hideticks()
    subplots_adjust(0,0,1,1)

def enable_tex():
    from matplotlib import rc
    rc('text', usetex=True)
    rc('font', family='serif')

