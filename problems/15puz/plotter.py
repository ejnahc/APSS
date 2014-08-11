# -*- coding: utf-8 -*-

import math
from matplotlib import rc, use
from matplotlib.pyplot import rcdefaults
from matplotlib.pylab import *
import matplotlib.font_manager as fm
import json

def plot_series(series, guidelines={}):
    data = json.loads(open("comparison.json").read())
    clf()
    fpl = fm.FontProperties(fname="/usr/share/fonts/truetype/nanum/"
        "NanumGothic.ttf", size=14)

    lg = lambda x: math.log(x,2)
    if guidelines:
        min_x = 0
        max_x = max(data[s]["d"][-1] for s in series)
        x = [min_x, max_x]
        print guidelines
        for guideline_label, guideline in guidelines.iteritems():
            plot(x, [lg(guideline(xx)) for xx in x], "--", color="0.5", lw=8,
                    label=guideline_label, alpha=0.5)
    series_name = {"ids": u"점점 깊어지는 탐색", 
        "bfs": u"너비 우선 탐색",
        "bidir": u"양방향 탐색"}
    for marker, s in zip("sdo", series):
        plot(data[s]["d"], map(lg, data[s]["states"]), 'k'+marker+'-', 
                ms=8, mfc='w',
                label=series_name[s])
    gca().legend(loc="best",prop=fpl)
    xlim(0.5,xlim()[1]+0.5)
    ylabels = [10]
    while lg(ylabels[-1] * 10) <= ylim()[1]:
        ylabels.append(ylabels[-1] * 10)
    yticks(map(lg,ylabels), map(str,ylabels))
    grid(True)
    xlabel(u"목표 상태까지의 최단 거리", fontproperties=fpl)
    gca().set_aspect("equal")

    show()
