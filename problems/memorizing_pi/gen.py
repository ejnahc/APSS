from random import *
print 50
for cc in range(50):
    n = randint(10,10000)
    ret = ""
    for i in range(n):
        ret = ret + chr(ord('0') + randint(0,9))
    print ret

