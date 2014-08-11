rl = lambda: raw_input().strip()
cases = int(rl())
seen = set()
def find(board, y, x, word, s):
    if (y, x, s) in seen: return False
    seen.add((y, x, s))
    if s == len(word): return True
    if not (0 <= y < 5 and 0 <= x < 5): return False
    if word[s] != board[y][x]: return False
    for dx in xrange(-1, 2):
        for dy in xrange(-1, 2):
            if dx or dy:
                if find(board, y + dy, x + dx, word, s+1):
                    return True
    return False
for cc in xrange(cases):
    board = [rl() for i in xrange(5)]
    w = int(rl())
    for i in xrange(w):
        word = rl()
        seen = set()
        if any(find(board, i, j, word, 0) for i in xrange(5) for j in
               xrange(5)):
            print word, 'YES'
        else:
            print word, 'NO'
