# -*- coding: utf-8 -*-

from itertools import *
from common import *

def bars(heights):
    for x, h in zip(count(), heights):
        box(0, x, h, x+1, color="0.9", edgecolor="k")
    hideticks()


def plot1():
    clf()
    subplot(1,3,1)
    title("(a)")
    bars([7, 1, 5, 9, 6, 7, 3])
    xlim(-0.5, 7.5); ylim(0, 9.5)
    subplot(1,3,2)
    title("(b)")
    bars([7, 1, 5, 9, 6, 7, 3])
    box(0, 2, 5, 6, color='0.5', alpha=0.5)
    xlim(-0.5, 7.5); ylim(0, 9.5)
    subplot(1,3,3)
    title("(c)")
    bars([7, 1, 5, 9, 6, 7, 3])
    fill([3, 2, 5, 6], [0, 3, 4, 1], color='0.5', alpha=0.5, edgecolor='k')
    xlim(-0.5, 7.5); ylim(0, 9.5)
    subplots_adjust(left=0.05,right=0.95)
    show()

def plot2():
    clf()
    subplot(1,3,1)
    title("(a)")
    bars([7, 1, 5, 9, 6, 7, 3])
    plot([4,4],[-0.5,9.5], 'k--', linewidth=4)
    xlim(-0.5, 7.5); ylim(0, 9.5)
    subplot(1,3,2)
    title("(b)")
    bars([7, 1, 5, 9, 6, 7, 3])
    plot([4,4],[-0.5,9.5], 'k--', linewidth=4)
    box(0, 3, 6, 5, color='0.5', alpha=0.5)
    xlim(-0.5, 7.5); ylim(0, 9.5)
    subplot(1,3,3)
    title("(c)")
    bars([7, 1, 5, 9, 6, 7, 3])
    #plot([4,4],[-0.5,9.5], 'k--', linewidth=4)
    box(0, 2, 5, 5, ls='dashed', lw=2, fill=False)
    box(0, 3, 6, 6, ls='dashed', lw=2, fill=False)
    xlim(-0.5, 7.5); ylim(0, 9.5)
    subplots_adjust(left=0.05,right=0.95)
    show()

def plot3():
    plots = [(3,4),(3,5),(2,5),(2,6),(1,6),(0,6)]
    h = [7,1,5,9,6,7,3]
    clf()
    for i, (x1, x2) in zip(range(6), plots):
        subplot(2,3,i+1)
        bars(h)
        plot([4,4],[-0.5,9.5],'k--', linewidth=2)
        box(0, x1, min(h[x1:x2+1]), x2+1, color='0.5', alpha=0.5)
    show()
def plot4():
    clf()
    box(0, 0, 6, 5, ls='dashed', lw=2, fill=False)
    text(0.2, 5.5, 'R', size=25)
    text(6.6, 3.5, "R'", size=25)
    box(0, 2, 4, 7, ls='dashed', lw=2, fill=False)
    plot([3,3],[-0.5,7.5], 'k--', linewidth=4)
    box(0, 1.5, 6, 2, color='0.5', alpha=0.5)
    box(0, 5.5, 4, 6, color='0.5', alpha=0.5)
    text(1.7, 0.25, 'A')
    text(5.7, 0.25, 'B')
    arr(6.2, 0, 6.2, 5, both_dir=True)
    text(2.4, 6.3, 'W')
    arr(4.2, 2, 4.2, 7, both_dir=True)
    text(4.4, 4.3, 'W')
    xlim(-1,8)
    ylim(-0.5,7)
    hideticks()
    subplots_adjust(left=0.05,right=0.95)
    show()
plot1()
