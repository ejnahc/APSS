# -*- coding: utf-8 -*-
from random import *
from math import *

def ranged(a,b):
    return random()*(b-a)+a

def bisect(ew, eh, cw, ch):
    if ew >= cw: return eh >= ch
    if ew < ch: return False
    lo, hi = 0, pi / 2.0
    for it in xrange(100):
        mid = (lo+hi)/2
        if cos(mid)*cw + cos(pi/2-mid)*ch <= ew:
            hi = mid
        else:
            lo = mid
    return sin(hi)*cw + cos(hi)*ch <= eh

def solve(ew, eh, cw, ch):
    return bisect(ew, eh, cw, ch) or bisect(ew, eh, ch, cw)

def getRandom():
    while True:
        ew, eh = ranged(0.01,100), ranged(0.01,100)
        if ew < eh: ew, eh = eh, ew
        cw = ranged(ew, hypot(eh,ew)*0.98)
        lo, hi = 0, eh
        for i in xrange(8):
            mid = (lo+hi)/2
            if solve(ew, eh, cw, mid):
                lo = mid
            else:
                hi = mid
        ch = ranged(lo, hi)

        expected = solve(ew, eh, cw, ch)
        if expected and not solve(ew-1e-7, eh-1e-7, cw, ch): continue
        if not expected and solve(ew+1e-7, eh+1e-7, cw, ch): continue
        return (ew, eh, cw, ch, "YES" if expected else "NO")

def getTrivial():
    ew, eh = ranged(0.01, 100), ranged(0.01, 100)
    cw, ch = ranged(0.01, ew-0.01), ranged(0.01, eh-0.01)
    ret = "YES"
    if random() < 0.5:
        ew, cw, eh, ch = cw, ew, ch, eh
        ret = "NO"
    return ew, eh, cw, ch, ret

if __name__ == "__main__":
    cases = ([getTrivial] + [getRandom] * 9) * 5
    shuffle(cases)
    input = open("envelopes.in", "w")
    output = open("envelopes.out", "w")
    input.write("%d\n" % len(cases))
    for gen in cases:
        ew, eh, cw, ch, ret = gen()
        if random() < 0.5: ew, eh = eh, ew
        if random() < 0.5: cw, ch = ch, cw

        input.write("%.10lf %.10lf %.10lf %.10lf\n" % (ew, eh, cw, ch))
        output.write("%s\n" % ret)
    input.close()
    output.close()
