# -*- coding: utf-8 -*-

from random import randint as rnd
examples = ["321 3", "123 3", "422 2", "12738173912 7"]
cases = [5]*6 + [8]*5 + [10]*5 + [14]*30
print len(examples) + len(cases)
for ex in examples:
    print ex
for sz in cases:
    print "".join(map(str, [rnd(0,9) for i in xrange(sz)])), rnd(2,20)

