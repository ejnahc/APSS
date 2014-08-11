# -*- coding: utf-8 -*-
from pylab import *

poly = []
cut = []

def run():
    input = open("input.txt", "w")
    input.write("%d %d %d %d\n" % (cut[0][0], cut[0][1], cut[1][0],
        cut[1][1]))
    input.write("%d\n" % len(poly))
    for x, y in poly:
        input.write("%d %d\n" % (x, y))
    input.close()

    import subprocess
    sp = subprocess.Popen("./a.out polycut < input.txt > output.txt", shell=True)
    sp.communicate()

    lines = open("output.txt", "r").readlines()
    ret = []
    for line in lines:
        coords = map(float, line.split())
        ret.append(zip(coords[0::2], coords[1::2]))
        print coords
    return ret

def save():
    return poly, cut

def load(x):
    global poly, cut
    poly, cut = x
    vis()

def vis():
    clf()
    grid(True)

    if len(poly) >= 3 and len(cut) == 2:
        cutpolys = run()
        for cp in cutpolys:
            fill([p[0] for p in cp], [p[1] for p in cp], '#ccaaaa', lw=0)

    if len(poly) > 0:
        plot([p[0] for p in poly] + [poly[0][0]],
            [p[1] for p in poly] + [poly[0][1]],
            'ko-', ms=8)
    if len(cut) > 0:
        plot([p[0] for p in cut],
            [p[1] for p in cut],
            'ro', ms=8)
        if len(cut) == 2:
            x1, y1 = cut[0]
            x2, y2 = cut[1]
            plot([x1,x2,x2,x1,x1],[y1,y1,y2,y2,y1],'r-',lw=1)



    gca().set_aspect("equal")
    xlim((0,100))
    ylim((0,100))
    xticks(range(0,101,10))
    yticks(range(0,101,10))

    show()

def onclick(event):
    x, y = int(event.xdata + 0.5), int(event.ydata + 0.5)
    #print "click (%d,%d) button %d" % (x, y, event.button)
    if event.button == 1:
        poly.append((x,y))
    else:
        global cut
        if len(cut) == 2: cut = []
        cut.append((x,y))
    vis()

def onkeypress(event):
    if event.key == "escape":
        global poly
        poly = []
        vis()

if __name__ == "__main__":
    fig = figure(2)
    if "button_cid" in globals():
        fig.canvas.mpl_disconnect(button_cid)
        fig.canvas.mpl_disconnect(key_cid)
    button_cid = fig.canvas.mpl_connect('button_press_event', onclick)
    key_cid = fig.canvas.mpl_connect('key_press_event', onkeypress)
    vis()
