#include <iostream>
#include <vector>

using namespace std;

// FenwickTree tree(100000);
// tree.add(1, 2);
struct FenwickTree {
    vector<int> tree;
    FenwickTree(int n) : tree(n+1) { }

    int sum(int pos) {
        ++pos;
        int ret = 0;
        while (pos > 0) {
            ret += tree[pos];
            pos &= (pos - 1);
        }

        return ret;
    }

    void add(int pos, int val) {
        ++pos;
        while(pos < tree.size()) {
            tree[pos] += val;
            pos += (pos & -pos);
        }
    }
};