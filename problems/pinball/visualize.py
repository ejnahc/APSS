# -*- coding: utf-8 -*-

import matplotlib
from common import *
import numpy


def draw(circles, pos, dir):
    dir = dir / norm(dir)

    clf()
    subplots_adjust(0.05,0.05,0.95,0.95)
    for i, (x, y, r) in enumerate(circles):
        plot([x],[y],'ko',ms=5)
        circle(y, x, r, 'k-')
        text(x+1, y+1, str(i), size=20)

    # projection of a onto b
    def projection(a, b):
        b = b / norm(b)
        return b * dot(a, b)

    def simulate(pos, dir, circles):
        mincircle = None
        mint = 1e200
        for i, (x, y, r) in enumerate(circles):
            center = array([x, y], dtype=float)
            v = center - pos
            # (here + t * dir - center) ^ 2 == (radius+1) ^ 2
            coefs = [dot(dir, dir),
                2*(dot(dir, pos) - dot(dir, center)),
                dot(pos,pos) + dot(center,center) - 2 * dot(pos, center) -
                (r+1.)**2]
            #print coefs
            #import pdb; pdb.set_trace()
            for t in roots(coefs):
                if isinstance(t, numpy.complex): continue
                if t >= 1e-9 and mint > t:
                    mint = t
                    mincircle = center
                    mincircle_index = i
        if mincircle == None: return None
        print "mincircle_index %d" % mincircle_index
        point_of_contact = pos + mint * dir
        print "circle to point_of_contact: %g circle rad: %g" % (norm(mincircle -
            point_of_contact), circles[mincircle_index][2])
        from_center = point_of_contact - mincircle
        displacement = pos - point_of_contact
        there = pos - 2 * (displacement - projection(displacement, from_center))
        direction = there - point_of_contact
        return point_of_contact, direction / norm(direction)

    steps = 0
    while steps < 100:
        next = simulate(pos, dir, circles)
        circle(pos[1], pos[0], 1, 'k-')
        if next:
            arrow(pos[0], pos[1], dir[0]*3, dir[1]*3, head_length=0.5, head_width=1)
        else:
            arrow(pos[0], pos[1], dir[0]*12, dir[1]*12, head_length=0.5, head_width=1)
            break
        npos, ndir = next
        plot([pos[0], npos[0]], [pos[1], npos[1]], 'k--')
        pos, dir = next
        print "pos", pos, "dir", dir
        steps += 1

    print steps, 'steps'


    xlim((0,100))
    ylim((0,100))
    gca().set_aspect("equal")
    hideticks()
    show()
    return steps

def gen():
    import numpy.random as r
    px = int(r.random() * 100)
    py = int(r.random() * 100)
    dx = int(r.random() * 20) - 10
    dy = int(r.random() * 20) - 10

    check = [(px, py, 0)]
    circles = []
    tries = max(10, int(r.normal() * 10) + 500)
    for t in range(tries):
        cx = int(r.random() * 100)
        cy = int(r.random() * 100)
        cr = max(1, min(100, int(r.normal() * 10) + 15))
        assert 0 <= cx <= 100
        assert 0 <= cy <= 100
        assert 0 <= cr <= 100
        ok = True
        for x, y, rd in check:
            if (x-cx)**2 + (y-cy)**2 <= (cr+rd+2)**2:
                ok = False
                break
        if ok:
            circles.append((cx, cy, cr))
            check.append((cx, cy, cr))
    return circles, array([px, py], dtype=numpy.float64), array([dx, dy],
                                                                dtype=numpy.float64)

# circles = [(22, 40, 12), (61, 26, 20), (19, 78, 21), (51, 86, 7),
#         (84, 57, 15)]
# pos = array([5., 5.])
# dir = array([1., 1.])
def go(min=10):
    global circles, pos, dir
    while True:
        circles, pos, dir = gen()
        if draw(circles, pos, dir) >= min:
            break

taken = []

def take():
    savefig('%.2d.png' % len(taken))
    taken.append((circles, pos, dir))
    print 'taken', len(taken)

def save():
    f = open('input.txt', 'w')
    f.write('%d\n' % len(taken))
    for circles, pos, dir in taken:
        f.write('%.0lf %.0lf %.0lf %.0lf %d\n' % (pos[0], pos[1], dir[0],
                                                  dir[1], len(circles)))
        for c in circles:
            f.write('%d %d %d\n' % c)
    f.close()

