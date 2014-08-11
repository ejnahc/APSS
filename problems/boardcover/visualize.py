# -*- coding: utf-8 -*-

from common import *

def visualize(board):
    board = list(reversed(board))
    h, w = len(board), len(board[0])

    box(0, 0, h, w, edgecolor='k', color='white')
    for y in range(h):
        for x in range(w):
            if board[y][x] == '#':
                box(y, x, y+1, x+1, color="0.5", linewidth=0)
            if board[y][x].isdigit():
                box(y, x, y+1, x+1, color="0." + board[y][x], linewidth=0)
            if board[y][x].isalpha():
                box(y, x, y+1, x+1, color="0.8", linewidth=0)
            hthick = y + 1 < h and board[y+1][x] != board[y][x]
            if hthick: line(y+1, x, y+1, x+1, "k")
            vthick = x + 1 < w and board[y][x] != board[y][x+1]
            if vthick: line(y, x+1, y+1, x+1, "k")
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
    visualize(["##a##ee",
            "#aacdde",
            "#bccd##",
            "#bb####"])
    subplots_adjust(left=0.05,right=0.95)
    show()

def example2():
    clf()
    subplot(1,2,1)
    visualize([
        "#bbcdd#",
        "#baccd#",
        "##aa###"])
    subplot(1,2,2)
    visualize([
        "#bbccd#",
        "#bacdd#",
        "##aa###"])
    subplots_adjust(left=0.05,right=0.95)
    show()

def example3():
    clf()

    subplot(1,5,1)
    visualize([
        "#####",
        "##...",
        "....."])
    plot([2.5],[1.5],'k*',ms=12)

    subplot(1,5,2)
    visualize([
        "#####",
        "##99.",
        "..9.."])
    plot([2.5],[1.5],'k*',ms=12)

    subplot(1,5,3)
    visualize([
        "#####",
        "##99.",
        "...9."])
    plot([2.5],[1.5],'k*',ms=12)

    subplot(1,5,4)
    visualize([
        "#####",
        "##9..",
        "..99."])
    plot([2.5],[1.5],'k*',ms=12)

    subplot(1,5,5)
    visualize([
        "#####",
        "##9..",
        ".99.."])
    plot([2.5],[1.5],'k*',ms=12)

    for i in range(0,5):
        subplot(1,5,i+1)
        title("(%s)" % chr(ord('a')+i))
    subplots_adjust(left=0.05,right=0.95,top=0.8)
    show()
example3()
