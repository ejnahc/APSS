#include<cstring>
#include<algorithm>
#include<cstdio>
#include<cassert>
#include<cmath>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

const double EPSILON = 1e-8;
const double PI = 2.0 * acos(0.0);

// 2차원 벡터를 표현한다
struct vector2 {
	double x, y;
	explicit vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}

	// 두 벡터의 비교
	bool operator == (const vector2& rhs) const { return x == rhs.x && y == rhs.y; }
	bool operator < (const vector2& rhs) const { if(x != rhs.x) return x < rhs.x; return y < rhs.y; }

	// 벡터의 덧셈과 뺄셈
	vector2 operator + (const vector2& rhs) const { return vector2(x + rhs.x, y + rhs.y); }
	vector2 operator - (const vector2& rhs) const { return vector2(x - rhs.x, y - rhs.y); }
	vector2 operator - () const { return vector2(-x, -y); }

	// 스칼라로 곱셈
	vector2 operator * (double rhs) const { return vector2(x * rhs, y * rhs); }

	// 벡터의 길이를 반환한다
	double norm() const { return hypot(x, y); }

	// 방향이 같은 단위 벡터 (unit vector) 를 반환한다
	// 영벡터에 대해 호출한 경우 결과값은 정의되지 않는다
	vector2 normalize() const { double n = norm(); return vector2(x / n, y / n); }

	// x축의 양의 방향으로부터 이 벡터까지 반시계방향으로 잰 각도
	double polar() const { return fmod(atan2(y, x) + 2*PI, 2*PI); }

	// 내적/외적의 구현
	double dot(const vector2& rhs) const { return x * rhs.x + y * rhs.y; }
	double cross(const vector2& rhs) const { return x * rhs.y - rhs.x * y; }

	// 이 벡터를 rhs 에 사영한 결과
	vector2 project(const vector2& rhs) const {
		vector2 r = rhs.normalize();
		return r * r.dot(*this);
	}
};

// 원점에서 벡터 b 가 벡터 a 의 반시계 방향이면 양수, 시계 방향이면 음수, 평행이면 0 을 반환한다
double ccw(vector2 a, vector2 b) {
	return a.cross(b);
}

// 점 p 를 기준으로 벡터 b 가 벡터 a 의 반시계 방향이면 양수, 시계 방향이면 음수, 평행이면 0 을 반환한다
double ccw(vector2 p, vector2 a, vector2 b) {
	return ccw(a-p, b-p);
}


// (a,b) 를 포함하는 선과 (c,d) 를 포함하는 선의 교점을 x 에 반환한다.
// 두 선이 평행이면 (겹치는 경우를 포함) 거짓을, 아니면 참을 반환한다.
bool lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& x) {
	double det = (b - a).cross(d - c);
	if(det == 0) return false;
	x = a + (b - a) * ((c - a).cross(d - c) / det);
	return true;
}

// (a,b) 와 (c,d) 가 평행한 두 선분일 때 이들이 한 점에서 겹치나 확인한다
bool parallelSegments(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p) {
	if(b < a) swap(a, b);
	if(d < c) swap(c, d);
	// 두 선분이 겹치지 않는 경우를 우선 걸러낸다
	if(b < c || d < a) return false;
	// 두 선분은 확실히 겹친다. 교차점을 하나 찾자.
	if(a < c) p = c; else p = a;
	return true;
}

// p 가 (a,b) 를 감싸면서 각 변이 x,y축에 평행한 최소 사각형 내부에 있는지 확인한다.
// a, b, p 는 일직선 상에 있다고 가정한다.
bool inBoundingRectangle(vector2 p, vector2 a, vector2 b) {
	if(b < a) swap(a, b);
	return p == a || p == b || (a < p && p < b);
}

// (a,b) 선분과 (c,d) 선분의 교점을 p 에 반환한다.
// 교점이 여러 개 있을 경우 아무 것이나 반환한다.
// 두 선분이 교차하지 않을 경우 false 를 반환한다.
bool segmentIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p) {
	// 두 직선이 평행인 경우를 우선 예외로 처리한다
	if(!lineIntersection(a, b, c, d, p)) return parallelSegments(a, b, c, d, p);
	// p 가 두 선분에 포함되어 있는 경우에만 참을 반환한다
	return inBoundingRectangle(p, a, b) && inBoundingRectangle(p, c, d);

}

// 두 선분이 서로 접촉하는지 여부를 반환한다
bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d) {
	double ab = ccw(a, b, c) * ccw(a, b, d);
	double cd = ccw(c, d, a) * ccw(c, d, b);
	// 두 선분이 한 직선 위에 있는 경우
	if(ab == 0 && cd == 0) {
		if(b < a) swap(a, b);
		if(d < c) swap(c, d);
		return !(b < c || d < a);
	}
	return ab <= 0 && cd <= 0;
}

// 점 p 에서 (a,b) 직선에 내린 수선의 발을 구한다
vector2 perpendicularFoot(vector2 p, vector2 a, vector2 b) {
  return a + (p - a).project(b - a);
}

// 점 p 와 (a,b) 직선 사이의 거리를 구한다
double pointToLine(vector2 p, vector2 a, vector2 b) {
	return (p - perpendicularFoot(p, a, b)).norm();
}

// 주어진 단순 다각형 p 의 넓이를 구한다. p 는 각 꼭지점의 위치 벡터의 집합으로 주어진다.
double area(const vector<vector2>& p) {
	double ret = 0;
	for(int i = 0; i < p.size(); ++i) {
		int j = (i + 1) % p.size();
		ret = ret + (p[i].x * p[j].y - p[j].x * p[i].y);
	}
	return fabs(ret) / 2.0;
}

// 점 q 가 다각형 p 안에 포함되어 있을 경우 참, 아닌 경우 거짓을 반환한다.
// q 가 다각형의 경계 위에 있는 경우의 반환값은 정의되어 있지 않다.
bool isInside(vector2 q, const vector<vector2>& p) {
	int crosses = 0;
	for(int i = 0; i < p.size(); ++i) {
		int j = (i + 1) % p.size();
		// (p[i], p[j]) 가 반직선을 세로로 가로지르는가?
		if((p[i].y > q.y) != (p[j].y > q.y)) {
			double atX = (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y) + p[i].x;
			if(q.x < atX)
				++crosses;
		}
	}
	return crosses % 2 > 0;
}


typedef vector<vector2> polygon;

// points 에 있는 점들을 모두 포함하는 최소의 볼록 다각형을 찾는다.
// 볼록 다각형의 꼭지점은 제일 왼쪽 아래 점부터 시작해서 시계 방향으로 반환된다.
// 한 직선 위에 세 개 이상의 점이 있을 경우 가운데 것들은 무시된다.
polygon giftWrap(const vector<vector2>& points) {
	int n = points.size();
	polygon hull;

	// 가장 왼쪽 아래 점을 찾는다. 이 점은 껍질에 반드시 포함된다.
	vector2 pivot = *min_element(points.begin(), points.end());
	hull.push_back(pivot);

	while(true) {
		// (p - ph) 가 가장 왼쪽인 점을 찾는다. 평행인 점이 여러 개 있으면
		// 가장 먼 것을 선택한다.
		vector2 ph = hull.back(), next = points[0];
		for(int i = 1; i < n; i++) {
			double cross = ccw(ph, next, points[i]);
			double dist = (next - ph).norm() - (points[i] - ph).norm();
			if(cross > 0 || (cross == 0 && dist < 0))
				next = points[i];
		}
		// 시작점으로 돌아왔으면 종료한다.
		if(next == pivot) break;
		hull.push_back(next);
	}

	return hull;
}


// (a,b) 를 포함하는 직선으로 다각형 p 를 자른 뒤, (a,b) 의 왼쪽에 있는 부분들을 반환한다
polygon cutPoly(const polygon& p, const vector2& a, const vector2& b) {
	int n = p.size();
	vector<bool> inside(n);
	for(int i = 0; i < n; ++i)
		inside[i] = ccw(a, b, p[i]) >= 0;
	// 이외의 경우에는 일부는 직선 왼쪽에, 일부는 직선 오른쪽에 떨어진다
	polygon ret;
	for(int i = 0; i < n; ++i) {
		int j = (i + 1) % n;
		if(inside[i]) ret.push_back(p[i]);
		if(inside[i] != inside[j]) {
			vector2 intersection;
			assert(lineIntersection(p[i], p[j], a, b, intersection));
			ret.push_back(intersection);
		}
	}
	return ret;
}

polygon readPoly() {
	int n;
	cin >> n;
	polygon p(n);
	for(int i = 0; i < n; i++)
		cin >> p[i].x >> p[i].y;
	return p;
}

vector2 readVector() {
	vector2 ret;
	cin >> ret.x >> ret.y;
	return ret;
}

void writePoly(const polygon& p) {
	for(int i = 0; i < p.size(); i++)
		printf("%s%.15lf %.15lf", (i ? " " : ""), p[i].x, p[i].y);
	printf("\n");
}

void testConvexHull() {
	polygon p = readPoly();
	writePoly(giftWrap(p));
}

void testPolyCut() {
	double x1, y1, x2, y2;
	cin >> x1 >> y1 >> x2 >> y2;
	if(x1 > x2) swap(x1, x2);
	if(y1 > y2) swap(y1, y2);
	polygon p = readPoly();

	p = cutPoly(p, vector2(x1, y1), vector2(x2, y1));
	p = cutPoly(p, vector2(x2, y1), vector2(x2, y2));
	p = cutPoly(p, vector2(x2, y2), vector2(x1, y2));
	p = cutPoly(p, vector2(x1, y2), vector2(x1, y1));
	writePoly(p);
}

bool approx(vector2 a, vector2 b) {
	return fabs((a-b).norm()) < 1e-7;
}

int main(int argc, char* argv[]) {
	assert(vector2(1,0).cross(vector2(0,1)) > 0);
	assert(vector2(0,1).cross(vector2(1,1)) < 0);
	assert(fabs(vector2(1,1).polar() - PI/4) < 1e-9);
	vector2 a(1,1), b(0,1), c(1,0);
	assert(fabs((a-b-c).norm()) < 1e-9);
	assert(b.norm() == 1);
	assert(approx(vector2(4,0), vector2(4,9).project(vector2(127,0))));
	assert(ccw(vector2(1,1), vector2(-1,1)) > 0);
	assert(ccw(vector2(4,4), vector2(5,5), vector2(3,5)) > 0);
	assert(ccw(vector2(-1,1), vector2(1,1)) < 0);
	{
		vector2 a(1,0), b(-1,0), c(0.5,-1), d(0.5,1);
		vector2 p, q(0.5, 0);
		assert(lineIntersection(a,b,c,d,p) && approx(q,p));
		assert(lineIntersection(a,b,d,c,p) && approx(q,p));
		assert(lineIntersection(b,a,c,d,p) && approx(q,p));
		assert(lineIntersection(b,a,d,c,p) && approx(q,p));
		assert(lineIntersection(d,c,b,a,p) && approx(q,p));
		assert(!lineIntersection(a, b, vector2(2,0), vector2(3,0), p));
		assert(!lineIntersection(c, d, vector2(4,-7), vector2(4,-8), p));
		assert(segmentIntersection(a,b,c,d,p) && approx(q,p));
		assert(segmentIntersection(a,b,d,c,p) && approx(q,p));
		assert(segmentIntersection(b,a,c,d,p) && approx(q,p));
		assert(segmentIntersection(b,a,d,c,p) && approx(q,p));
		assert(segmentIntersection(d,c,b,a,p) && approx(q,p));
		assert(segmentIntersects(a,b,c,d));
		assert(!segmentIntersects(a,c,b,d));
		assert(!segmentIntersection(a, b, vector2(2,0), vector2(3,0), p));
		assert(!segmentIntersection(c, d, vector2(4,-7), vector2(4,-8), p));

		vector2 w(-1,-1), x(0,0), y(1,1), z(2,2);
		assert(!segmentIntersection(w, x, y, z, p));
		assert(segmentIntersection(w, x, x, z, p) && approx(x, p));
		assert(segmentIntersection(x, z, x, w, p) && approx(x, p));
		assert(segmentIntersection(x, y, x, z, p));
		assert(segmentIntersection(w, z, x, y, p));
		assert(segmentIntersection(z, w, x, y, p));
		assert(!segmentIntersects(w, x, y, z));
		assert(segmentIntersects(w, z, x, y));
		assert(segmentIntersects(w, x, x, y));
		assert(segmentIntersects(w, y, x, z));
	}

	assert(approx(perpendicularFoot(vector2(7,6), vector2(0,0), vector2(12,3)), vector2(8,2)));
	vector<vector2> poly;
	poly.push_back(vector2(0,0));
	poly.push_back(vector2(1,1));
	poly.push_back(vector2(1,2));
	poly.push_back(vector2(-1,1));
	assert(area(poly) == 2);

	// convex hull tests
	{
#define NOPAREN(...) __VA_ARGS__
#define TEST(_poly, _hull) {\
	vector2 poly[] = {NOPAREN _poly}, hull[] = {NOPAREN _hull}; \
	polygon res = giftWrap(polygon(poly, poly + sizeof(poly) / sizeof(vector2)));\
	if(res.size() != sizeof(hull) / sizeof(vector2)) \
		fprintf(stderr, "Expected %d Result %d\n", int(sizeof(hull) / sizeof(vector2)), int(res.size())); \
	assert(res.size() == sizeof(hull) / sizeof(vector2)); \
	for(int i = 0; i < res.size(); ++i) {\
		if(!(res[i] == hull[i])) \
			printf("Expected (%g,%g) Result (%g,%g)\n", hull[i].x, hull[i].y, res[i].x, res[i].y); \
		assert(res[i] == hull[i]); \
	} fprintf(stderr, "PASS\n"); }

		vector2 a(0,0), b(1,0), c(1,1), d(0,1), e(0.5,0.5), f(0.5,1.5);
		vector2 poly1[] = { b, a, c }, poly1h[] = { a, c, b };

		TEST((b,a,c), (a,c,b));
		TEST((c,b,a), (a,c,b));
		TEST((d,a,b,c), (a,d,c,b));
		TEST((b,d,a,c), (a,d,c,b));
		TEST((d,e,b,a,c), (a,d,c,b));
		TEST((d,b,e,f,a,c), (a,d,f,c,b));
		TEST((a,c,e,b), (a,c,b));
		TEST((a,d,c,e), (a,d,c));
		TEST((a,e,c), (a,c));
	}

	fprintf(stderr, "all good.\n");

	vector2 v;

	if(argc == 2 && strcmp(argv[1], "polycut") == 0)
		testPolyCut();
	else if(argc == 2 && strcmp(argv[1], "convex") == 0)
		testConvexHull();

}

