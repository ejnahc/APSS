#include<algorithm>
#include<cassert>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

const int MAX_SIZE = 1024;
char decompressed[MAX_SIZE][MAX_SIZE];

void decompress(string::iterator& it, int y, int x, int size) {
  char head = *it;
  ++it;

  if(head == 'b' || head == 'w') {
    for(int dy = 0; dy < size; ++dy)
      for(int dx = 0; dx < size; ++dx)
        decompressed[y+dy][x+dx] = head;
  }
  else {
    int half = size/2;
    decompress(it, y, x, half);
    decompress(it, y, x+half, half);
    decompress(it, y+half, x, half);
    decompress(it, y+half, x+half, half);
  }
}

string reverse(string::iterator& it) {
  char head = *it;
  ++it;

  if(head == 'b' || head == 'w')
    return string(1, head);
  string ul = reverse(it);
  string ur = reverse(it);
  string ll = reverse(it);
  string lr = reverse(it);
  return string("x") + ll + lr + ul + ur;
}

vector<string> resize(const vector<string>& original, int sz) {
  if(sz == original.size()) return original;
  vector<string> ret(sz, string(sz, 0));
  int factor = sz / original.size();
  for(int i = 0; i < sz; i++) {
    for(int j = 0; j < sz; j++) {
      ret[i][j] = original[i/factor][j/factor];
    }
  }
  return ret;
}

vector<string> merge(const vector<string>& ul, const vector<string>& ur,
                     const vector<string>& ll, const vector<string>& lr) {
  vector<string> ret;
  for(int i = 0; i < ul.size(); i++)
    ret.push_back(ul[i] + ur[i]);
  for(int i = 0; i < ll.size(); i++)
    ret.push_back(ll[i] + lr[i]);
  return ret;
}

vector<string> repr(string::iterator& it) {
  char head = *it;
  ++it;
  if(head == 'b') return vector<string>(1, string(1, '#'));
  if(head == 'w') return vector<string>(1, string(1, '.'));
  vector<string> ul = repr(it);
  vector<string> ur = repr(it);
  vector<string> ll = repr(it);
  vector<string> lr = repr(it);
  int sz = max(max(ul.size(), ur.size()), max(ll.size(), lr.size()));
  return merge(resize(ul, sz), resize(ur, sz), resize(ll, sz), resize(lr, sz));
}

int main() {
  int cases;
  cin >> cases;
  for(int cc = 0; cc < cases; ++cc) {
    string quadtree;
    cin >> quadtree;
    assert(quadtree.size() <= 1000);
    assert(quadtree.size() == 1 + 4 * count(quadtree.begin(), quadtree.end(), 'x'));
    string::iterator it = quadtree.begin();
    string reversed = reverse(it);
    cout << reversed << endl;
  }
}

