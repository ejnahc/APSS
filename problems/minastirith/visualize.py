# -*- coding: utf-8 -*-

from common import *

clf()
full()
#plt = gcf().add_subplot(111,frameon=False,xticks=[],yticks=[])
places = [(0.5, 10), (2.7, 5), (pi/2, 20), (pi, 12),
        (pi*1.2, 8), (pi*1.3, 12), (pi*0.1, 4), (pi*0.6, 22),
        (pi*1.8, 19), (pi*1.5, 12)]

#places = [(0, 20), (pi / 2, 20), (pi, 20), (1.55*pi, 13.5)]

def sched(y, x1, x2, lw, type):
    #x2 -= 0.1
    #box(y-0.2, x1, y+0.2, x2, edgecolor='0.0', color='0.4')
    line(y, x1, y, x2, "k"+type, lw=lw)
    line(y+0.05, x1, y-0.05, x1, "k", lw=lw)
    line(y+0.05, x2, y-0.05, x2, "k", lw=lw)

def separate(begin1, end1, begin2, end2, tolerance=0.5):
    # dirty hack
    from math import pi
    for i in xrange(-10,10):
        disjoint = (end1 + pi * i + tolerance < begin2 or
                end2 + tolerance < begin1 + pi * i)
        if not disjoint: return False
    return True

def get_layers(ranges):
    layers = []
    for begin, end in sorted(ranges,cmp=lambda p,q: cmp(p[0]-p[1], q[0]-q[1])):
        found = False
        for layer in layers:
            intersect = False
            for obegin, oend in layer:
                if not separate(obegin, oend, begin, end, 0.1):
                #if not ((end + 0.5 < obegin) or (oend + 0.5 < begin)):
                    intersect = True
                    break
            if not intersect:
                layer.append((begin, end))
                found = True
                break
        if not found:
            layers.append([(begin, end)])
    return layers

ranges = []
for ang, rad in places:
    ang = (ang + 0.5 * pi) % (2*math.pi)
    rad *= 8.0 / 20.0
    range = 2.0 * math.asin(rad / 16.0)
    ranges.append((ang - range, ang + range))

#plot_type = "linear"
plot_type = "circular"

if plot_type == "original":
    circle(0, 0, 8, 'k', lw=1)
    plot([0], [0], 'ko', ms=12)
    for ang, rad in places:
        ang += 0.5 * pi
        rad *= 8.0 / 20.0
        y = sin(ang) * 8
        x = cos(ang) * 8
        plot([x], [y], 'k*', ms=12)
        circle(y, x, rad, 'k:', color='0.3', lw=2)
elif plot_type == "circular":
    circle(0, 0, 8, 'k', lw=2)
    layers = get_layers(ranges)
    for level, layer in enumerate(layers):
        rad = 8.5 + 0.5 * level
        for begin, end in layer:
            arc(0, 0, rad, begin, end, "k--")
            for ang in [begin, end]:
                plot([(rad-0.1)*cos(ang), (rad+0.1)*cos(ang)],
                     [(rad-0.1)*sin(ang), (rad+0.1)*sin(ang)], 'k-')
    plot([0],[0],'ko',ms=10)
    plot([0,8],[0,0],'k:')
else:
    enable_tex()
    layers = get_layers(ranges)
    gap = 0.2
    minx = min(r[0] for r in ranges)
    maxx = max(r[1] for r in ranges)
    print "total layers", len(layers)
    for y in xrange(len(layers)):
        print "layer %d: " % y,
        print layers[y]
        for begin, end in layers[y]:
            sched(gap*y, begin, end, 2, "--")
    sched(-gap, 0, 2*math.pi, 4, "")
    #text(-0.5, -5*gap, "0", size=30)
    xlim(minx-0.1, maxx+0.1)
    ylim(-gap*2,gap*(len(layers)))

gca().set_aspect("equal")
print 1
print len(places)
for ang, rad in places:
    ang += 0.5 * pi
    rad *= 8.0 / 20.0
    y = sin(ang) * 8
    x = cos(ang) * 8
    print "%.8lf %.8lf %.2lf" % (y, x, rad)

hideticks()
subplots_adjust(0,0,1,1)
show()
