# -*- coding: utf-8 -*-
import sys

digits = [1]; n = 7
#digits = [3,5]; n = 9
#digits = [2,1,0]; n = 10

print """graph g{
   node[shape=circle];
   edge[color=gray50];"""

if len(sys.argv) > 1 and sys.argv[1] == "partial":
    for i in xrange(n):
        for d in digits:
            j = (i*10+d)%n
            print "%d -- %d [labelfontsize=18,dir=forward,taillabel=%d];" % (i,j,d)
else:
    label = lambda a: "%d%s" % (a % n, "a" if a < n else "b")
    for i in xrange(n):
        print "n%da [label=%d];" % (i,i)
        print "n%db [label=%d,style=filled,fillcolor=gray70];" % (i,i)
    for i in xrange(2*n):
        for d in digits:
            j = (i*10+d)%n
            if i*10+d >= n: j += n
            print "n%s -- n%s [labelfontsize=18,dir=forward,taillabel=%d];" % (
                    label(i), label(j), d)
print "}"

