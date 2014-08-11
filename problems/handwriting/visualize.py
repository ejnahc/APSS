# -*- coding: utf-8 -*-

words = "I am a boy buy".split()
mat = [line.strip().split() for line in
    """1.0 0.0 0.0 0.0 0.0
    0.1 0.6 0.1 0.1 0.1
    0.1 0.1 0.6 0.1 0.1
    0.1 0.1 0.1 0.6 0.1
    0.2 0.2 0.2 0.2 0.2""".split("\n")]

print """digraph G {
node [shape=ellipse]
rankdir=LR;
"""
for a in xrange(5):
    for b in xrange(5):
        if float(mat[a][b]) > 0:
            print "%s -> %s [label=%s];" % (words[a], words[b], mat[a][b])

print """}"""

