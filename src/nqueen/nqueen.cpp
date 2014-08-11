#include<cstdio>
#include<cstring>
#include<iostream>
#include<string>
#include<vector>
#include <sys/time.h>

double getTime() {
	timeval tv;
	gettimeofday(&tv, 0);
	return tv.tv_sec + tv.tv_usec * 1e-6;
}
using namespace std;
const int MAXN = 200;

int n;

bool col[MAXN], major[MAXN*2], minor[MAXN*2];

int classicNQueen(int y) {
	if(y == n) return 1;
	int ret = 0;
	for(int x = 0; x < n; x++)
		if(!col[x] && !major[y - x + n] && !minor[y + x]) {
			col[x] = major[y - x + n] = minor[y + x] = 1;
			ret += classicNQueen(y+1);
			col[x] = major[y - x + n] = minor[y + x] = 0;
		}
	return ret;
}

int classicNQueenSolve() {
	memset(col, 0, sizeof(col));
	memset(major, 0, sizeof(major));
	memset(minor, 0, sizeof(minor));
	return classicNQueen(0);
}

struct Node {
	int removed;
	Node* adj[3];
	Node *prev, *next;

	void init() {
		removed = 0;
		prev = next = NULL;
		for(int i = 0; i < 6; i++)
			adj[i] = NULL;
	}

	void remove() {
		if(removed++ == 0) {
			prev->next = next;
			next->prev = prev;
		}
	}

	void recover() {
		if(--removed == 0) {
			prev->next = this;
			next->prev = this;
		}
	}
};

Node matrix[MAXN][MAXN];
Node heads[MAXN], tails[MAXN];

int dancingLinksNQueen(int y) {
	if(y == n) return 1;
	int ret = 0;
	for(Node* here = heads[y].next; here != &tails[y]; here = here->next) {
		for(int dx = -1; dx <= 1; ++dx)
			for(Node* dis = here->adj[dx+1]; dis != NULL; dis = dis->adj[dx+1])
				dis->remove();
		ret += dancingLinksNQueen(y+1);
		for(int dx = -1; dx <= 1; ++dx)
			for(Node* dis = here->adj[dx+1]; dis != NULL; dis = dis->adj[dx+1])
				dis->recover();
	}
	return ret;
}

int dancingLinksNQueenSolve() {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			matrix[i][j].init();
			if(i + 1 < n) {
				for(int dx = -1; dx <= 1; dx++) {
					int nx = j + dx;
					if(0 <= nx && nx < n)
						matrix[i][j].adj[dx+1] = &matrix[i+1][nx];
				}
			}
			if(j + 1 < n) matrix[i][j].next = &matrix[i][j+1];
			if(j > 0) matrix[i][j].prev = &matrix[i][j-1];

		}
		heads[i].init();
		heads[i].next = &matrix[i][0];
		matrix[i][0].prev = &heads[i];

		tails[i].init();
		tails[i].prev = &matrix[i][n-1];
		matrix[i][n-1].next = &tails[i];
	}
	return dancingLinksNQueen(0);
}

int main() {
	for(int i = 3; i <= 20; ++i) {
		n = i;
		double t1 = getTime();
		printf("nq(%d) = %d\n", i, classicNQueenSolve());
		double t2 = getTime();
		printf("nq(%d) = %d\n", i, dancingLinksNQueenSolve());
		double t3 = getTime();
		printf("normal %.2lf dancing %.2lf\n", t2-t1, t3-t2);
	}

}

