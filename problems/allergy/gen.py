#!/usr/bin/python
# -*- coding: utf-8 -*-
import random, string
gen_name = lambda: "".join([random.choice(string.lowercase)
    for _ in xrange(random.randint(1, 10))])
CASES = 50
Ns = [5,10,20,30]+[50]*6
limits = [2,4,6,8,10,12,14,16,18]
print CASES
for cc in xrange(CASES):
    foods = Ns[cc % len(Ns)]
    limit = min(foods/2, limits[cc % len(limits)])
    friends = random.randint(10, 40)
    names = set()
    while len(names) < friends: names.add(gen_name())
    print friends, foods
    names = list(names)
    print " ".join(names)
    eaters = [[] for _ in xrange(foods)]
    for i in xrange(friends):
        for food in random.sample(xrange(foods), random.randint(1,limit)):
            eaters[food].append(names[i])
    for e in eaters:
        print len(e), " ".join(e)

