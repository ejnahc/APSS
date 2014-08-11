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


// (a,b) 를 포함하는 선과 (c,d) 를 포함하는 선의 교점을 p 에 반환한다.
// 두 선이 평행이면 (겹치는 경우를 포함) 거짓을, 아니면 참을 반환한다.
bool lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p) {
	double det = (b - a).cross(d - c);
	if(det == 0) return false;
	p = a + (b - a) * ((c - a).cross(d - c) / det);
	return det;
}

// (a,b) 와 (c,d) 가 평행한 두 선분일 때 이들이 한 점에서 겹치나 확인한다
bool parallelSegments(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p) {
	if(b < a) swap(a, b);
	if(d < c) swap(c, d);
	if(b == c) { p = b; return true; }
	if(a == d) { p = a; return true; }
	return false;
}

// p 가 (a,b) 를 감싸면서 각 변이 x,y축에 평행한 최소 사각형 내부에 있는지 확인한다
bool inBoundingRectangle(vector2 p, vector2 a, vector2 b) {
	double x1 = a.x, x2 = b.x, y1 = a.y, y2 = b.y;
	if(x1 > x2) swap(x1, x2);
	if(y1 > y2) swap(y1, y2);
	return x1 <= p.x && p.x <= x2 && y1 <= p.y && p.y <= y2;
}

// (a,b) 선분과 (c,d) 선분의 교점을 p 에 반환한다.
// 두 선분이 교차하지 않거나, 하나 이상의 교점이 있으면 거짓을 반환한다.
bool segmentIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p) {
	// 두 직선이 평행인 경우를 우선 예외로 처리한다
	if(!lineIntersection(a, b, c, d, p)) return parallelSegments(a, b, c, d, p);
	// p 가 두 선분에 포함되어 있는 경우에만 참을 반환한다
	return inBoundingRectangle(p, a, b) && inBoundingRectangle(p, c, d);

}

// 두 구간 [a,b], [c,d] 가 교집합이 없는지 여부를 확인한다
double disjoint(double a, double b, double c, double d) {
	if(a > b) swap(a, b); if(c > d) swap(c, d);
	return b < c || d < a;
}

// 두 선분이 서로 접촉하는지 여부를 반환한다
bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d) {
	double ab = ccw(a, b, c) * ccw(a, b, d);
	double cd = ccw(c, d, a) * ccw(c, d, b);
	// 두 선분이 한 직선 위에 있는 경우
	if(ab == 0 && cd == 0)
		return !disjoint(a.x, b.x, c.x, d.x) &&
			!disjoint(a.y, b.y, c.y, d.y);
	return ab <= 0 && cd <= 0;
}

// 점 p 에서 (a,b) 직선에 내린 수선의 발을 구한다
vector2 perpendicularFoot(vector2 p, vector2 a, vector2 b) {
	vector2 delta = (b - a).normalize();
	return a + delta * (p - a).dot(delta);
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

// points 에 있는 점들을 모두 포함하는 최소의 볼록 다각형을 찾는다
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
			double cross = (next - ph).cross(points[i] - ph);
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
		inside[i] = ((b-a).cross(p[i]-a) >= 0);
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

// 두 다각형이 서로 닿거나 겹치는지 여부를 반환한다.
// 한 점이라도 겹친다면 true 를 반환한다.
bool polygonIntersects(const polygon& p, const polygon& q) {
	int n = p.size(), m = q.size();
	// 우선 한 다각형이 다른 다각형에 포함되어 있는 경우를 확인하자
	if(isInside(p[0], q) || isInside(q[0], p)) return true;
	// 이외의 경우, 두 다각형이 서로 겹친다면 서로 닿는 두 변이 반드시 존재한다
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			if(segmentIntersects(p[i], p[(i+1)%n], q[j], q[(j+1)%m]))
				return true;
	return false;
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
	int cases;
	scanf("%d", &cases);
	while(cases--) {
		vector<vector2> inputs[2];
		int n;
		scanf("%d", &n);
		for(int i = 0; i < n; i++) {
			int t, x, y;
			scanf("%d %d %d", &t, &x, &y);
			inputs[t].push_back(vector2(x, y));
		}
		polygon hulls[2];
		for(int i = 0; i < 2; i++) hulls[i] = giftWrap(inputs[i]);
		if(polygonIntersects(hulls[0], hulls[1]))
			printf("THEORY IS INVALID\n");
		else
			printf("THEORY HOLDS\n");
	}
}

