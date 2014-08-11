import random, string
CNT = [1, 2, 4, 8, 26]
print 50

def get_word(board, transform, alphabets):
    y, x = random.randint(0, 4), random.randint(0, 4)
    word = []
    while len(word) < 10:
        word.append(board[y][x])
        while True:
            dx, dy = random.randint(-1, 1), random.randint(-1, 1)
            if dx or dy:
                x2 = x + dx
                y2 = y + dy
                if 0 <= x2 < 5 and 0 <= y2 < 5:
                    y = y2
                    x = x2
                    break

    if transform % 3 > 0:
        if transform % 3 == 1:
            idx = len(word) - 1
        else:
            idx = random.randint(0, len(word) - 1)
        if transform % 2 == 0:
            newchar = random.choice(string.uppercase)
        else:
            newchar = random.choice(alphabets)
        word[idx] = newchar

    return ''.join(word)

for cases in range(50):
    alphabets = list(string.uppercase)
    random.shuffle(alphabets)
    cnt = CNT[cases % len(CNT)]
    alphabets = alphabets[:cnt]

    board = [''.join([random.choice(alphabets) for i in xrange(5)])
             for j in xrange(5)]

    words = [get_word(board, cases * 3 + i, alphabets) for i in xrange(10)]

    print '\n'.join(board)
    print len(words)
    for w in words: print w
    
