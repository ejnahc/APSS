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
            if board[y][x].isalpha():
                thin = "0.9"
            else:
                thin = "0.8"
            line(y+1, x, y+1, x+1, "k" if hthick else thin,
                    lw=2 if hthick else 1)
            vthick = x + 1 < w and board[y][x] != board[y][x+1]
            line(y, x+1, y+1, x+1, "k" if vthick else thin,
                    lw=2 if vthick else 1)
    hideticks()
    show()

def example1():
    clf()
    visualize([
        "e....",
        "eabb.",
        ".aac.",
        "..cc.",
        "...dd"])
    subplots_adjust(left=0.05,right=0.95)
    show()

def example2():
    clf()
    subplot(131)
    title("(a)")
    visualize([
        ".....",
        ".abb.",
        ".aab.",
        ".....",
        "....."])
    subplot(132)
    title("(b)")
    visualize([
        ".....",
        ".abb.",
        ".acc.",
        ".....",
        "....."])
    subplot(133)
    title("(c)")
    visualize([
        ".....",
        ".abc.",
        ".abc.",
        ".....",
        "....."])
    subplots_adjust(left=0.05,right=0.95)
    show()
example2()
