# -*- coding: utf-8 -*-

from common import *
from math import asin
from matplotlib import rc

rc('text', usetex=True)
rc('font', family='serif')

clf()
plt = gcf().add_subplot(111,frameon=False,xticks=[],yticks=[])

ang, rad = pi * 0.5, 5
plot([0], [0], 'ko', ms=12)
y = sin(ang) * 8
x = cos(ang) * 8

font_size=40
range = 2.0 * asin(rad / 2. / 8.)

def fig3():
    places = [(0.5, 10), (2.7, 5), (pi/2, 20), (pi, 12),
            (pi*1.2, 8), (pi*1.3, 12), (0, 4), (pi*0.6, 22),
            (pi*1.7, 19), (pi*1.5, 12)]
    it = 0
    circle(0, 0, 8, 'k--', lw=1)
    for it in xrange(len(places)):
        ang, rad = places[it]
        ang = (ang + 0.5 * pi) % (2*pi)
        rad *= 8.0 / 20.0
        y = sin(ang) * 8
        x = cos(ang) * 8
        #plot([x], [y], 'k*', ms=12)
        if it == 8:
            circle(y, x, rad, 'k--', color='k', lw=3)

            range = 2.0 * asin(rad / 16.)
            #plot([0,cos(ang)*8], [0,sin(ang)*8], 'k-', lw=1)
            plot([0,cos(ang+range)*8], [0,sin(ang+range)*8], 'k-', lw=1)
            plot([0,cos(ang-range)*8], [0,sin(ang-range)*8], 'k-', lw=1)
            plot([0,8],[0,0],'k-',lw=1)

            # end_i
            angles = arange(0, ang+range, 0.001)
            plot(cos(angles)*1.5, sin(angles)*1.5, 'k-', lw=1)
            t = (ang+range)/2
            arr(sin(t)*1.5, cos(t)*1.5, sin(t)*3, cos(t)*3, head_sz=0.3)
            text(cos(t)*3.2, sin(t)*3.2, '$end_{i}$', size=font_size*0.5)

            # begin_i
            angles = arange(0, 2*pi+ang-range, 0.001)
            plot(cos(angles)*1, sin(angles)*1, 'k-', lw=1)
            t += pi
            arr(sin(t)*1, cos(t)*1, sin(t)*3, cos(t)*3, head_sz=0.3)
            text(cos(t)*3.2-1.5, sin(t)*3.2-1, '$begin_{i}$', size=font_size*0.5)
            #text(cos(t)*1.5-1.5, sin(t)*1.5, '$begin_{i}$', size=font_size*0.5)

            # rest of the big circle
            angles = arange(0, 2*pi - 2*range, 0.001) + ang + range
            plot(cos(angles)*8, sin(angles)*8, 'k-', lw=3)
            print angles
        else:
            continue
            circle(y, x, rad, 'k:', color='0.3', lw=2)
            range = 2.0 * asin(rad / 16.)
            sz = 0.5
            plot([cos(ang-range)*(8-sz/2), cos(ang-range)*(8+sz/2)],
                    [sin(ang-range)*(8-sz/2), sin(ang-range)*(8+sz/2)] , 'k', lw=2)
            plot([cos(ang+range)*(8-sz/2), cos(ang+range)*(8+sz/2)],
                    [sin(ang+range)*(8-sz/2), sin(ang+range)*(8+sz/2)] , 'k', lw=2)


def fig2():
    circle(0, 0, 8, 'k', lw=2)
    # watchtower
    plot([x], [y], 'k*', ms=12)
    circle(y, x, rad, ':', color='0.3', lw=2)
    # two triangles
    plot([x, cos(ang-range)*8, 0, x], [y, sin(ang-range)*8, 0, y], 'k--', lw=6)
    plot([x, cos(ang+range)*8, 0, x], [y, sin(ang+range)*8, 0, y], 'k')

    # labels
    text(cos(ang-range-0.1)*3, sin(ang-range-0.1)*3, '8', size=font_size*0.6)
    text(cos(ang-0.05)*3, sin(ang-0.05)*3, '8', size=font_size*0.6)
    text(cos(ang-range*0.25)*6.2, sin(ang-range*0.25)*6.2, r'$\frac{r}{2}$', size=font_size)
    text(cos(ang-range*0.75)*6.2, sin(ang-range*0.75)*6.2, r'$\frac{r}{2}$', size=font_size)

    # line dividing one triangle
    midx = (x+cos(ang-range)*8)/2
    midy = (y+sin(ang-range)*8)/2
    plot([0, midx], [0, midy], 'k')

    # perpendicular sign
    center = array([midy, midx])
    delta = array([sin(ang-range)*8 - y, cos(ang-range)*8 - x])
    delta = delta / norm(delta) * 0.2
    delta2 = array([-delta[1], delta[0]])
    ps = [center + delta, center + delta + delta2,
            center - delta + delta2,
            center - delta]
    plot([p[1] for p in ps], [p[0] for p in ps], 'k')

    # theta
    angles = arange(ang-range, ang-range*0.5+0.0001,0.001)
    plot(cos(angles)*1.5, sin(angles)*1.5, 'k')
    text(cos(ang-range*0.75)*1.7, sin(ang-range*0.75)*1.7, r'$\theta$', size=24)

    ylim(-0.5, 13.5)

def fig1():
    circle(0, 0, 8, 'k', lw=2)
    # watchtower
    plot([x], [y], 'k*', ms=12)
    circle(y, x, rad, ':', color='0.3', lw=2)

    # lines
    plot([8,0,0],[0,0,8],'k')
    plot([cos(ang-range)*8,0,cos(ang+range)*8],
         [sin(ang-range)*8,0,sin(ang+range)*8], 'k')

    # begin_i
    arc(0, 0, 0.5, 0, ang-range, 'k')
    t = (ang-range)/2
    arr(sin(t)*0.5, cos(t)*0.5, sin(t)*4.5, cos(t)*4.5, head_sz=0.3)
    text(cos(t)*4.6, sin(t)*4.6,
            r"$begin_{i}$", size=font_size*0.75)

    # end_i
    arc(0, 0, 0.9, 0, ang+range, 'k')
    t = (ang+range)*0.6
    arr(sin(t)*0.9, cos(t)*0.9, sin(t)*4.4, cos(t)*4.4, head_sz=0.3)
    text(cos(t)*4.6-0.5, sin(t)*4.6,
            r"$end_{i}$", size=font_size*0.75)

    # loc
    arc(0, 0, 1.2, 0, ang, 'k--')
    t = pi/12
    arr(sin(t)*1.2, cos(t)*1.2, sin(t)*3.0, cos(t)*3, head_sz=0.3)
    text(cos(t)*3.2+0.2, sin(t)*3.2-0.2, r'$loc$', size=font_size*0.75)

    # range
    arc(0, 0, 1.6, ang, ang+range, 'k--')
    t = pi/2 + range/2
    arr(sin(t)*1.6, cos(t)*1.6, sin(t)*3.0, cos(t)*3.0, head_sz=0.3)
    text(cos(t)*3.2-1.5, sin(t)*3.2, r'$range$',
            size=font_size*0.75)

    # covered
    angles = arange(ang-range, ang+range+0.0001,0.001)
    plot(cos(angles)*8.0, sin(angles)*8.0, 'k--', lw=6)


    ylim(-0.5, 13.5)
    pass

fig3()
hideticks()
subplots_adjust(0,0,1,1)
gca().set_aspect("equal")
show()
