import random
cases = 50

print cases
for cc in range(cases):
    n = random.randint(1,100)
    if cc < 5: n = 10
    if cc > 45: n = 100
    print n, random.randint(1,10)
    print " ".join(map(str, [random.randint(1,1000) for i in range(n)]))

