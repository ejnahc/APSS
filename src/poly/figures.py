# -*- coding: utf-8 -*-

from pylab import *
import matplotlib.font_manager as fm
fpl = fm.FontProperties(fname="/usr/share/fonts/truetype/nanum/"
                "NanumGothic.ttf", size=14)

def figure1():
    clf()
    p = poly([1,3,5,6,8])
    p[-1] -= 17
    axhline(0, color="k")
    x = arange(0.75,8.4,0.05)
    plot(x, polyval(p,x),'k-',label="f(x)")
    rts = [r for r in roots(p) if r.imag == 0]
    plot(rts, [0 for r in rts], 'ko', ms=8, label=u"근")

    q = polyder(p)
    rts = [r for r in roots(q) if r.imag == 0]
    plot(rts, [polyval(p,r) for r in rts], 'k*', ms=12, label=u"극점")
    yticks([-100,-50,0,50])

    legend(loc="best",prop=fpl)
    grid()
    show()

