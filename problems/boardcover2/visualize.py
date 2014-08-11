# -*- coding: utf-8 -*-

from common import *

def visualize(board, label=False):
    board = list(reversed(board))
    h, w = len(board), len(board[0])

    box(0, 0, h, w, edgecolor='k', color='white')
    for y in range(h):
        for x in range(w):
            if board[y][x] == '#':
                oy, ox = y, x
    for y in range(h):
        for x in range(w):
            clr = 1.0
            if board[y][x] == '#':
                clr = 0.5
            if board[y][x].isdigit():
                clr = float("0." + board[y][x])
            if board[y][x].isalpha():
                clr = 0.8
            if clr < 1.0:
                box(y, x, y+1, x+1, color=("%.1lf" % clr), linewidth=0)
            if board[y][x] == '#' and label:
                text(x+0.2, y+0.4, "(%d, %d)" % (oy - y, x - ox), size=16,
                        color="white")
            thinclr = "%.1lf" % (0.9 if clr == 1.0 else clr + 0.1)
            hthick = y + 1 < h and board[y+1][x] != board[y][x]
            line(y+1, x, y+1, x+1, "k" if hthick else thinclr)
            vthick = x + 1 < w and board[y][x] != board[y][x+1]
            line(y, x+1, y+1, x+1, "k" if vthick else thinclr)
    hideticks()
    show()

def example1():
    clf()
    subplot(1,2,1)
    visualize(["##.##..",
               "#......",
               "#....##",
               "#..####"])
    subplot(1,2,2)
    visualize(["##.##c.",
               "#bbccc.",
               "#baaa##",
               "#ba####"])
    subplots_adjust(left=0.05,right=0.95)
    show()
#example1()

def example2():
    clf()
    visualize([".#.",
               "###",
               "..#"], True)
    show()

example2()
