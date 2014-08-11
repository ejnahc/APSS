#!/usr/bin/python
# -*- coding: utf-8 -*-
import sys, re
import numpy as np

pattern = re.compile("[^A-Za-z?!.]")

def log(message, *args):
    sys.stderr.write((message % args) + "\n")

def to_stream(filename):
    for line in open(filename):
        for tok in pattern.split(line):
            tok = tok.strip()
            if tok:
                yield tok

def to_sentences(stream):
    sentence = []
    for word in stream:
        w = word.rstrip("!?.")
        if w: sentence.append(w)
        if word[-1] in "!?.":
            yield sentence
            sentence = []

def to_filtered_sentences(stream, top_words, replace=True):
    w = len(top_words)
    word_dict = {}
    for i in xrange(w): word_dict[top_words[i]] = i
    for sent in stream:
        if replace:
            sentence = [word_dict[word] for word in sent if word in word_dict]
        else:
            sentence = [word for word in sent if word in word_dict]
        if len(sentence) == 0: continue
        yield sentence

def incr(dic, key):
    dic[key] = dic.get(key, 0) + 1

def get_top_words(corpus, cnt):
    count = {}
    sentences = 0
    for sentence in to_sentences(to_stream(corpus)):
        for word in sentence:
            incr(count, word)
        sentences += 1
    log("Processed %d sentences. Recognized %d words.", sentences,
            len(count))
    words = list(count.items())
    words.sort(cmp=lambda a,b: cmp(b[1], a[1]))
    log("Top 10 words and their count: %s",
            " ".join(["%s (%d)" % tup for tup in words[:10]]))
    return [word for word, cnt in words[:cnt]]

def normalize_matrix(matrix):
    for i in xrange(len(matrix)):
        s = np.sum(matrix[i])
        if s > 0:
            matrix[i] /= s
        else:
            matrix[i][i] = 1.0

def get_stats(corpus, top_words):
    w = len(top_words)
    begin_cnt = np.zeros(w)
    transition_cnt = np.zeros((w, w))
    for sentence in to_filtered_sentences(to_sentences(to_stream(corpus)),
        top_words):
        begin_cnt[sentence[0]] += 1
        for a, b in zip(sentence, sentence[1:]):
            transition_cnt[a][b] += 1
    begin_cnt /= np.sum(begin_cnt)
    normalize_matrix(transition_cnt)
    begin = list(reversed(np.argsort(begin_cnt)[-10:]))
    log("Top 10 words beginning sentences: %s",
            " ".join(["%s (%.3lf%%)" % (top_words[idx], begin_cnt[idx]*100.0)
                for idx in begin]))
    log("Words most likely to follow those words:")
    for idx in begin:
        next = np.argmax(transition_cnt[idx])
        log("    %s %s (%.3lf%%)", top_words[idx], top_words[next],
                transition_cnt[idx][next] * 100.0)
    return begin_cnt, transition_cnt

def edit_distance(a, b):
    n, m = len(a), len(b)
    d = np.zeros((n+1, m+1))
    for i in xrange(n+1): d[i][0] = i
    for j in xrange(m+1): d[0][j] = j
    for i in xrange(1,n+1):
        for j in xrange(1,m+1):
            if a[i-1] == b[j-1]:
                d[i][j] = d[i-1][j-1]
            else:
                d[i][j] = min(d[i-1][j], d[i][j-1], d[i-1][j-1]) + 1
    return d[n][m]

def generate_misclassifications(top_words):
    log("Generating artificial misclassification rate ..")
    from numpy.random import normal
    w = len(top_words)
    mis = np.zeros((w, w))
    for i in xrange(w):
        for j in xrange(i+1):
            distance = edit_distance(top_words[i], top_words[j])
            mis[i][j] = max(0.0, normal(0.4 ** distance, 0.05))
            mis[j][i] = max(0.0, normal(0.4 ** distance, 0.05))
    normalize_matrix(mis)
    mostly_wrong = list(sorted([(mis[i][i], i) for i in xrange(w)]))
    log("Top 10 words likely to be wrong:")
    for prob, idx in mostly_wrong[:10]:
        log("    %s (%.3lf%%) => %s", top_words[idx], prob*100.0,
                " ".join(["%s (%.3lf%%)" % (top_words[cand],
                    mis[idx][cand]*100.0)
                    for cand in reversed(np.argsort(mis[idx])[-4:])]))
    log("Top 10 words likely to be right:")
    for prob, idx in mostly_wrong[-10:]:
        log("    %s (%.3lf%%) => %s", top_words[idx], prob*100.0,
                " ".join(["%s (%.3lf%%)" % (top_words[cand],
                    mis[idx][cand]*100.0)
                    for cand in reversed(np.argsort(mis[idx])[-4:])]))
    return mis

def sample(iterable, N):
    from random import randint
    picked = []
    seen = 0
    for it in iterable:
        seen += 1
        if len(picked) < N:
            picked.append(it)
        elif randint(1, seen) <= N:
            idx = randint(0, N-1)
            picked[idx] = it
    return picked

def filter_short_sentences(iter, threshold=10):
    for it in iter:
        if len(it) >= threshold:
            yield it

def sample_test_cases(corpus, top_words, tests):
    sentences = to_sentences(to_stream(corpus))
    filtered = to_filtered_sentences(sentences, top_words, replace=False)
    return sample(filter_short_sentences(filtered), tests)

def mutate_test_cases(cases, top_words, mis):
    from numpy.random import random
    w = len(top_words)
    word_dict = {}
    for i in xrange(w): word_dict[top_words[i]] = i
    for sentence in cases:
        for i in xrange(len(sentence)):
            csum = mis[:,word_dict[sentence[i]]].cumsum()
            sentence[i] = top_words[csum.searchsorted(random()*csum[-1])]

def main():
    if len(sys.argv) != 4:
        print ("Usage) %s (corpus filename) (use top # words) (# test cases)" %
                sys.argv[0])
        return

    corpus, words, tests = sys.argv[1], int(sys.argv[2]), int(sys.argv[3])
    top_words = get_top_words(corpus, words)
    assert len(top_words) == words
    assert len(" ".join(top_words).split()) == words
    beginning, transition = get_stats(corpus, top_words)
    misclassified = generate_misclassifications(top_words)

    test_cases = sample_test_cases(corpus, top_words, tests)
    mutate_test_cases(test_cases, top_words, misclassified)
    print words, len(test_cases)
    print " ".join(top_words)
    print " ".join(["%.6lf" % prob for prob in beginning])
    for i in xrange(words):
        print " ".join(["%.6lf" % prob for prob in transition[i]])
    for i in xrange(words):
        print " ".join(["%.6lf" % prob for prob in misclassified[i]])
    for case in test_cases:
        print "%d %s" % (len(case), " ".join(case))

if __name__ == "__main__":
    main()
