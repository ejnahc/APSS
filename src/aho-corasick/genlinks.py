# -*- coding: utf-8 -*-

#words = ["ab", "bc", "ca", "bca", "caa"]
#words = ["apple", "led", "lapse"]
#words = ["SEVEN", "EVEN", "VEND", "EVE"]
import sys
words = sys.argv[1:] or ["CACHE", "CHEF", "ACHY", "ACHE"]
for w in words: print "%s [peripheries=2];" % w
prefixes = set()
forward = set()
prefixes.add("")
for w in words:
    for i in xrange(len(w)):
        prefixes.add(w[:i+1])
        forward.add((w[:i], w[:i+1]))
for a, b in forward:
    print (a or "empty"), "->", b, "[label=%s]" % b[-1], ";"
backward = set()
for w in words:
    for i in xrange(len(w)):
        suffix = w[1:i+1]
        while suffix not in prefixes:
            suffix = suffix[1:]
        backward.add((w[:i+1], suffix))
print "edge [dir=back,style=dashed];"
for a, b in backward:
    print (b or "empty"), "->", a, ";"
