# -*- coding: utf-8 -*-
from common import *
from StringIO import StringIO

node_names = []
label = {}
edges = []
def new_node():
    name = "node%d" % len(node_names)
    node_names.append(name)
    return name

def split(grid, y1, x1, sz):
    seen = set()
    for i in range(sz):
        for j in range(sz):
            seen.add(grid[y1+i][x1+j])
    if len(seen) == 1:
        node = new_node()
        res = ("b" if seen.pop() == "#" else "w")
        label[node] = res
        return res, node
    half = sz/2
    line(y1+half, x1, y1+half, x1+sz, 'k--', lw=4)
    line(y1, x1+half, y1+sz, x1+half, 'k--', lw=4)
    ret = "x"
    node = new_node()
    label[node] = "x"
    compressed, child = split(grid, y1+half, x1, half)
    edges.append((node, child))
    ret += compressed
    compressed, child = split(grid, y1+half, x1+half, half)
    edges.append((node, child))
    ret += compressed
    compressed, child = split(grid, y1, x1, half)
    edges.append((node, child))
    ret += compressed
    compressed, child = split(grid, y1, x1+half, half)
    edges.append((node, child))
    return ret, node

def draw(grid):
    N = len(grid)
    clf()
    for i in range(N):
        line(0, i, N, i, 'k')
        line(i, 0, i, N, 'k')
    for i in range(N):
        for j in range(N):
            if grid[i][j] == '#':
                box(i, j, i+1, j+1, color='0.5')
    compressed, node = split(grid, 0, 0, N)
    print "Compressed:", compressed
    print """Graphviz:
digraph quadtree {
node [shape=circle];
"""
    for node in node_names:
        print "%s[label=%s];" % (node, label[node])
    for a,b in edges:
        print "%s -> %s;" % (a,b)
    print """}"""
    hideticks()
    show()

g = [
    "....############",
    "....############",
    "....############",
    "....############",
    "........########",
    "........########",
    "####....########",
    "..##....########",
    "....####........",
    "....####........",
    "....####........",
    "....####........",
    "............####",
    "............####",
    "..............##",
    "..............##"]

def plot1():
    draw(g)

def drawhorzbars(labels):
    n = len(labels)
    half = n / 2
    # plot will be centered at (half,half)
    LG = 0.6
    SG = 0.3
    for i in range(half):
        # LU
        y1, x1 = half+LG/2+i, half-n/2-LG/2
        y2, x2 = y1+(1-SG), x1+n/2
        box(y1,x1,y2,x2,color='0.9')
        text((x1+x2)/2, y1+0.1, labels[half-i-1])
        # RU
        x1 += n/2+LG
        x2 += n/2+LG
        box(y1,x1,y2,x2,color='0.9')
        text((x1+x2)/2, y1+0.1, labels[half-i-1])
        # RD
        y1 -= n/2+LG/2
        y2 -= n/2+LG/2
        box(y1,x1,y2,x2,color='0.9')
        text((x1+x2)/2, y1+0.1, labels[n-i-1])
        x1 -= n/2+LG
        x2 -= n/2+LG
        box(y1,x1,y2,x2,color='0.9')
        text((x1+x2)/2, y1+0.1, labels[n-i-1])

    line(half, -1, half, n+1, 'k')
    line(-1, half, n+1, half, 'k')
    """
    for i in range(n):
        box(i, 0, i+0.7, n/2.0-0.15, color='0.9')
        box(i, n/2.0+0.15, i+0.7, n-0.3, color='0.9')
        text(n/4.0, i+0.1, labels[n-i-1])
        text(3*n/4.0, i+0.1, labels[n-i-1])
    line(n/2.0-0.15, -0.3, n/2.0-0.15, n, 'k')
    line(-0.3, n/2.0, n, n/2.0, 'k')
    """
    ylim(-LG/2, n+LG/2)
    xlim(-SG-LG/2,n+SG+LG/2)
    #xlim(ylim())

def plot2():
    N = 8
    clf()
    subplot(131)
    drawhorzbars(range(1,N+1))
    #bar(range(N), range(1,N+1), color='0.5')
    hideticks()
    title("(a)")
    subplot(132)
    drawhorzbars(range(N/2,0,-1)+range(N,N/2,-1))
    #bar(range(N), range(N/2,0,-1)+range(N,N/2,-1), color='0.5')
    hideticks()
    title("(b)")
    subplot(133)
    #bar(range(N), range(N,0,-1), color='0.5')
    drawhorzbars(range(N,0,-1))
    hideticks()
    title("(c)")
    subplots_adjust(left=0.05,right=0.95)
    show()

plot2()
