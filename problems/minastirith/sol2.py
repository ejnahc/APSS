# -*- coding: utf-8 -*-

from common import *
from matplotlib import rc
from math import *

rc('text', usetex=True)
rc('font', family='serif')

full()
circle(0, 0, 8, 'k--')

# circle i
ang, rad = 0.15 * pi, 6
range = 2 * asin(rad / 16.)
circle(sin(ang)*8, cos(ang)*8, rad, 'k--')
text(cos(ang)*10, sin(ang)*10, r'$i$', size=32)
arc(0, 0, 8, ang+range, 2*pi+ang-range, 'k', lw=2)
plot([cos(ang+range)*7.8,cos(ang+range)*8.2],
        [sin(ang+range)*7.8,sin(ang+range)*8.2], 'k', lw=2)
plot([cos(ang-range)*7.8,cos(ang-range)*8.2],
        [sin(ang-range)*7.8,sin(ang-range)*8.2], 'k', lw=2)

text(cos(ang+range)*8.5, sin(ang+range)*8.5, 'begin', size=24)
text(cos(ang-range)*8.5, sin(ang-range)*8.5, 'end', size=24)

# line
len = 8*2*pi*0.6666
lo = -len/2
hi = lo + len
line(-12, lo, -12, hi, 'k--', lw=1)
text(lo-0.1, -11.4, '$0$', size=16)
line(-11.8, lo, -12.2, lo, 'k', lw=2)
text(hi-0.5, -11.4, '$2\pi$', size=16)
line(-11.8, hi, -12.2, hi, 'k', lw=2)

# begin-end
begin = lo + (ang + range) * len / (2*pi)
end = lo + (ang - range + 2 * pi) * len / (2*pi)
line(-12, begin, -12, end, 'k', lw=2)
text(begin-1, -11.4, 'begin', size=16)
line(-11.8, begin, -12.2, begin, 'k', lw=2)
text(end-1.2, -11.4, 'end', size=16)
line(-11.8, end, -12.2, end, 'k', lw=2)

# circle A
ang, rad = 1.1 * pi, 4
range = 2 * asin(rad / 16.)
circle(sin(ang)*8, cos(ang)*8, rad, 'k--')
text(cos(ang)*10, sin(ang)*10, r'$a$', size=32)

# line A
beginA = (ang - range) * len / (2 * pi) + lo
endA = (ang + range) * len / (2 * pi) + lo
line(-11.8, beginA, -13.0, beginA, 'k', lw=2)
line(-11.8, endA, -13.0, endA, 'k', lw=2)
arr(-12.5, beginA, -12.5, endA-0.5, head_sz=0.3)
arr(-12.5, endA, -12.5, beginA+0.5, head_sz=0.3)
text((beginA+endA)/2-0.5, -14.0, r'$a$', size=16)

# circle B
ang, rad = 1.9 * pi, 5
range = 2 * asin(rad / 16.)
circle(sin(ang)*8, cos(ang)*8, rad, 'k--')
text(cos(ang-0.1*pi)*10, sin(ang-0.1*pi)*10, r'$b$', size=32)

# line B
for add in xrange(2):
    beginB = (ang - range - add * 2 * pi) * len / (2 * pi) + lo
    endB = (ang + range - add * 2 * pi) * len / (2 * pi) + lo
    line(-11.8, beginB, -13.0, beginB, 'k', lw=2)
    line(-11.8, endB, -13.0, endB, 'k', lw=2)
    arr(-12.5, beginB, -12.5, endB-0.5, head_sz=0.3)
    arr(-12.5, endB, -12.5, beginB+0.5, head_sz=0.3)
    text((beginB+endB)/2-0.5, -14.0, r'$b$(?)', size=16)



plot([0,8],[0,0],'k')
text(8.5, -0.5, r'$0$', size=32)

xl = xlim()
xlim((xl[0]-0.5, xl[1]+0.5))
ylim((-14.5,11.5))
gca().set_aspect("equal")
show()

