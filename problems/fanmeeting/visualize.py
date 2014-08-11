# -*- coding: utf-8 -*-

from common import *
def draw(members, fans, rows, cols):
    figures = len(fans) + len(members) - 1
    clf()
    assert rows*rows >= figures
    for shift in xrange(figures):
        subplot(rows, cols, shift+1)
        gca().set_aspect("equal")
        for i, ch in enumerate(members):
            box(1, i, 2, i+1, color="0.9")
            text(i+0.5, 1.5, ch, size=12, ha="center", va="center") 
        for i, ch in enumerate(fans):
            x = len(members)-1-shift+i
            box(0, x, 1, x+1, color="0.9")
            text(x+0.5, 0.5, ch, size=12, ha="center", va="center") 
        hideticks()
        xlim((-len(fans)+1,figures+1))
        title("(%s)" % chr(ord('a') + shift))
    subplots_adjust(0.05,0.05,0.95,0.95)
    show()

draw("abcd", "012345", 3, 3)
