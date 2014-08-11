# -*- coding: utf-8 -*-
from pylab import *
from common import *
import math

import matplotlib.font_manager as fm
fpl = fm.FontProperties(fname="/usr/share/fonts/truetype/nanum/"
        "NanumGothic.ttf", size=14)

class Turtle(object):
    def __init__(self, y, x, dir, *args, **kwargs):
        self.y, self.x, self.dir = y, x, dir
        self.args, self.kwargs = args, kwargs

    def move(self, amt):
        dy, dx = math.sin(self.dir), math.cos(self.dir)
        self.x += dx * amt
        self.y += dy * amt
        return self

    def forward(self, amt):
        dy, dx = math.sin(self.dir), math.cos(self.dir)
        plot([self.x, self.x + dx * amt],
                [self.y, self.y + dy * amt], *self.args, **self.kwargs)
        self.x += dx * amt
        self.y += dy * amt
        return self

    def turn(self, amt):
        self.dir = math.fmod(self.dir + amt + 2*math.pi, 2*math.pi)
        return self

def cardwidth(cw, ch, theta):
    return cos(theta)*cw + cos(math.pi/2-theta)*ch

def cardheight(cw, ch, theta):
    return sin(theta)*cw + cos(theta)*ch

def figure5(samples=16):
    clf()
    w, h = 4, 2
    ts = arange(0,pi/2,pi/2/samples)
    tups = list(sorted(zip(cardwidth(w, h, ts), cardheight(w, h, ts))))
    bar(left=0,bottom=0,height=4.3,width=3.7,color='0.85',lw=0)
    for x, y in tups:
        bar(left=0,bottom=0,height=y,width=x,fill=False,edgecolor='0.6')
    plot([t[0] for t in tups], [t[1] for t in tups], 'ko')
    xlim(0,max([t[0] for t in tups])*1.1)
    ylim(0,max([t[1] for t in tups])*1.1)
    gca().set_aspect("equal")
    xlabel(u"최소 사각형의 너비", fontproperties=fpl)
    ylabel(u"최소 사각형의 높이", fontproperties=fpl)



def rectangle(y, x, dir, w, h, *args, **kwargs):
    t = Turtle(y,x,dir,*args,**kwargs)
    t.forward(w).turn(pi/2).forward(h).turn(pi/2).forward(w)
    t.turn(pi/2).forward(h)

def figure4():
    clf()
    enable_tex()
    rectangle(0, 1, 0.4, 4, 1.5, 'k-')
    text(cos(0.4)*2+1, sin(0.4)*2+0.1, "$w$", rotation=0.4, size=24)
    text(cos(0.4+pi/2)*0.7+1.1, sin(0.4+pi/2)*0.7, "$h$", size=24)
    arc(0, 1, 0.5, 0, 0.4, 'k-')
    arc(0, 1, 0.2, 0.4+pi/2, pi, 'k-')
    arc(0, 1, 0.18, 0.4+pi/2, pi, 'k-')
    text(1+cos(0.2)*0.6, sin(0.2)*0.3, r'$\theta$', size=24)
    text(0.5+cos(3*pi/4+0.2)*0.2, sin(3*pi/4+0.2)*0.2, r'$\frac{\pi}{2}-\theta$',
            size=24)
    text(1,1,r'$w\cdot \cos \theta$', size=24)
    text(2,1,r'$w\cdot \sin \theta$', size=24)
    text(3,1,r'$h\cdot \cos \left( \frac{\pi}{2}-\theta \right)$', size=24)
    text(4,1,r'$h\cdot \cos \theta$', size=24)


    overall_width = cos(0.4)*4 + cos(pi/2-0.4)*1.5
    overall_height = sin(0.4)*4 + cos(0.4)*1.5
    # bounding rect
    t = Turtle(0,1-cos(pi/2-0.4)*1.5,0,'k--')
    t.move(overall_width).turn(pi/2).forward(overall_height).turn(pi/2)
    t.forward(overall_width).turn(pi/2).forward(overall_height)

    def rightAngle(y, x, a, amt=0.1):
        t = Turtle(y, x, a, 'k-')
        t.move(amt).turn(pi/2).forward(amt).turn(pi/2).forward(amt)

    rightAngle(0,1,0.4)
    rightAngle(sin(0.4)*4, cos(0.4)*4+1, 0.4+pi/2)
    arc(sin(0.4)*4, cos(0.4)*4+1, 0.3, pi/2, 0.4+pi/2, 'k-')
    rightAngle(overall_height, cos(0.4)*4+1-1.5*sin(0.4), 0.4+pi)
    rightAngle(sin(pi/2-0.4)*1.5, 1-cos(pi/2-0.4)*1.5, 2*pi-(pi/2-0.4))
    w = cos(pi/2-0.4)*1.5
    rightAngle(0,1+overall_width-w,pi/2)
    rightAngle(overall_height, 1+overall_width-w,pi)
    rightAngle(overall_height, 1-w, pi*3/2.)
    rightAngle(0, 1-w, 0)
    line(0,0,0,overall_width+w,'k-')
    a = gca()
    a.set_aspect("equal")
    a.set_axis_off()
    hideticks()
    subplots_adjust(0,0,1,1)
    show()

#figure4()

def figure3():
    clf()
    subplot(121)
    title("(a)")
    box(0, 0, 6, 8, color="0.8")
    #rectangle(0,0,0,8,6,color="0.4",lw=1,ls="-")
    xlim((-1,9))
    ylim((-1,7))
    a = gca()
    a.set_aspect("equal")
    hideticks()

    w, h = 8.2, 1.5
    for theta in arange(0,pi/2+0.0001,pi/10):
        rectangle(0, cos(pi/2-theta)*h, theta, w, h, color="k", lw=2)
    expand()
    subplot(122)
    title("(b)")
    box(0, 0, 6, 8, color="0.8")
    xlim((-1,9))
    ylim((-1,7))
    a = gca()
    a.set_aspect("equal")
    hideticks()

    w, h = 8.2, 1.5
    for theta in arange(0,pi/2+0.0001,pi/10):
        rectangle(0, cos(pi/2-theta)*w, theta, h, w, color="k", lw=2)
    expand()

    subplots_adjust(0.05,0.05,0.95,0.95)
    show()

def figure2():
    clf()
    rectangle(0,0,0,8,6,color="k",lw=1,ls="--")
    xlim((-1,9))
    ylim((-1,7))
    a = gca()
    a.set_aspect("equal")
    hideticks()
    from gen import ranged
    for i in xrange(12):
        y, x = ranged(0,6), ranged(0,8)
        dir = ranged(0,pi*2)
        rectangle(y,x,dir,8.2,1.5,color="k",lw=2,alpha=0.4)

    subplots_adjust(0.05,0.05,0.95,0.95)
    show()

def draw_all(ew, eh, cw, ch, theta,flipped=False):
    # draw envelope
    box(0, 0, eh, ew, color="0.8")
    #rectangle(0,0,0,ew,eh,color="black",lw=1,ls="--")

    tilted_cardwidth = cardwidth(cw, ch, theta)
    shift = (ew - tilted_cardwidth) / 2.0 + math.cos(math.pi/2-theta)*ch
    # draw card
    if not flipped:
        t = Turtle(0,shift,theta,lw=2,color="black")
    else:
        y = ch*sin(pi/2-theta)
        x = ew
        t = Turtle(y,x,pi-theta,lw=2,color="black")
    t.forward(cw).turn(pi/2).forward(ch).turn(pi/2).forward(cw)
    t.turn(pi/2).forward(ch)
    margin = max(ew/10,1.0)
    xlim((-margin,ew+margin))
    ylim((-margin,eh+margin))
    hideticks()
    a = gca()
    a.set_aspect("equal")
    a.set_axis_off()

def figure1():
    pi = math.pi
    clf()
    subplot(131)
    draw_all(8,6,8.2,1.5,0.465842)
    subplot(132)
    draw_all(8,6,8,4,0)
    subplot(133)
    draw_all(100,100,120,21,0.781129,True)
    subplots_adjust(0.05,0.05,0.95,0.95,wspace=0.1)
    show()

