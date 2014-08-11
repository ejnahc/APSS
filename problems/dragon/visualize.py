# -*- coding: utf-8 -*-
from common import *

sier = {"init": "A", "replace": {"A": "B-A-B", "B": "A+B+A"}, "delta": pi / 3}
dragon = {"init": "FX", "replace": {"X": "X+YF", "Y": "FX-Y"}, "delta": pi / 2}
koch = {"init": "F", "replace": {"F": "F+F-F-F+F"}, "delta": pi / 2}

def fractal(n, ruleset):
    dir = ruleset["init"]
    replace = ruleset["replace"]
    for i in xrange(n):
        next = ""
        for ch in dir:
            next += replace.get(ch, ch)
        dir = next
    return dir

def draw(n, ruleset, color='b', width=0.1):
    delta = ruleset["delta"]
    y, x, minx, miny, maxx, maxy, ang = 0, 0, 0, 0, 0, 0, pi / 4
    clf()
    ax = gcf().add_subplot(111,frameon=False,xticks=[],yticks=[])
    for ch in fractal(n, ruleset):
        if ch == "+":
            ang += delta
        elif ch == "-":
            ang -= delta
        else:
            dy, dx = sin(ang), cos(ang)
            ax.plot([x,x+dx], [y,y+dy], color=color, lw=width)
            y += dy
            x += dx
        minx = min(minx, x)
        miny = min(miny, y)
        maxx = max(maxx, x)
        maxy = max(maxy, y)
    h, w = maxy - miny, maxx - minx
    sz = max(h,w)
    midy = (maxy + miny) * 0.5
    midx = (maxx + minx) * 0.5
    ylim(midy-sz*0.55,midy+sz*0.55)
    xlim(midx-sz*0.55,midx+sz*0.55)
    print sz

    hideticks()
    subplots_adjust(0,0,1,1)
    gca().set_aspect("equal")
    show()

