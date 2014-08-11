#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <memory.h>

using namespace std;

// https://algospot.com/judge/problem/read/SOLONG
const int ALPHABETS = 26; // A-Z
int toNumber(char ch) { return ch - 'A'; }

struct TrieNode {
    TrieNode* children[ALPHABETS];

    int terminal;
    int first;
    TrieNode() : terminal(-1) { first=-1; memset(children,0,sizeof(children)); }
    ~TrieNode() {
        for (int i=0; i<ALPHABETS; i++)
            if (children[i])
                delete children[i];
    }

    void insert(const char* key, int id) {
        if (first == -1) first = id;
        if (*key == 0)
            terminal = id;
        else {
            int next = toNumber(*key);
            if (children[next] == NULL)
                children[next] = new TrieNode();

            children[next]->insert(key+1, id);
        }
    }

    TrieNode* find(const char* key) {
        if (*key == 0) return this;
        int next = toNumber(*key);
        if (children[next] == NULL)
            return NULL;
        return children[next]->find(key+1);
    }

    int type(const char* key, int id) {
        if (*key == 0) return 0;

        if (first == id) return 1;
        int next = toNumber(*key);
        return 1 + children[next]->type(key+1, id);
    }
};

int countKeys(TrieNode* trie, const char* word) {
    TrieNode* node = trie->find(word);
    if (node == NULL || node->terminal == -1)
        return strlen(word);

    return trie->type(word, node->terminal);
}