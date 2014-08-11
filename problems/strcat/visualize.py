# -*- coding: utf-8 -*-


nodes = map(lambda var: (var,),[3,1,1,3,4])

nodecnt = 0
def dfs(fp, node):
    global nodecnt
    nodecnt += 1
    nodeid = "node%d" % nodecnt
    if len(node) == 1:
        fp.write("%s [label=%d,shape=circle];\n" % (nodeid, node[0]))
    else:
        fp.write("%s [label=%d,shape=rectangle];\n" % (nodeid, node[0]))
        left = dfs(fp, node[1])
        right = dfs(fp, node[2])
        fp.write("%s -- %s; %s -- %s;\n" % (nodeid, left, nodeid, right))
    return nodeid

lev = 0
while True:
    fp = open("progress%d.dot" % lev, "w")
    fp.write("graph g {\n")
    nodecnt = 0
    for node in nodes:
        dfs(fp, node)
    fp.write("}")
    fp.close()
    if len(nodes) == 1: break
    nodes.sort()
    a, b = nodes[:2]
    print "merging %s and %s" % (a,b)
    for nd in nodes:
        print nd
    nodes = nodes[2:]
    nodes.append((a[0]+b[0], a, b))
    lev += 1

