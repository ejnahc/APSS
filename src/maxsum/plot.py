# -*- coding: utf-8 -*-
from matplotlib.pylab import *
from collections import defaultdict
data = defaultdict(lambda:[])
for line in open("data.txt").readlines():
    if not line.strip(): continue
    (label, n, time) = line.strip().split(",")
    data[label].append((n, time))
n = 0
clf()
type = ["o-", "*--", "s-", "x-."]
labels = ["N^3", "N^2", "NlgN", "N"]
for label, t in zip(labels, type):
    val = data[label]
    n = max(n, len(val))
    lw = 1.2 if len(t) == 2 else 2
    ms = 8
    if t[0] == "x": ms = 10
    if t[0] == "*": ms = 12
    mew = 0 if t[0] != "x" else 2
    plot(range(len(val)), [v[1] for v in val], t, color="k", lw=lw, 
            ms=ms, label=label, mew=mew)
def txt(n):
    return str(n)
    if n >= 1024*1024: return "%.1lfM" % (n / (1024.*1024))
    if n >= 1024: return "%.1lfK" % (n / (1024.))
    return str(n)
xticks(xrange(n), [txt(10*(2**i)) for i in xrange(n)], rotation=30)
subplots_adjust(0.05,0.2,0.95,0.95)
ylim(-0.5,7)
xlim(-0.5,n+0.5)
grid(True)
xlabel("Size of array (N)")
ylabel("Running time (second)")
axhline(0,lw=1,color='k')
legend(loc="best")
show()
