#include<cstdlib>
#include<cstdio>
#include<cassert>
#include<algorithm>
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

typedef vector<vector2> polygon;

// 시계 반대방향으로 주어진 볼록 다각형에서 가장 먼 꼭지점 쌍 사이의 거리를 반환한다.
double diameter(const polygon& p) {
	int n = p.size();

	// 가장 왼쪽에 있는 점과 오른쪽에 있는 점을 우선 찾는다
	int left = min_element(p.begin(), p.end()) - p.begin();
	int right = max_element(p.begin(), p.end()) - p.begin();

	// p[left] 와 p[right] 에 각각 수직선을 붙인다. 두 수직선은 서로 정반대 방향을 가리키므로,
	// A 의 방향만을 표현하면 된다.
	vector2 calipersA(0, 1);
	double ret = (p[right] - p[left]).norm();

	// toNext[i] = p[i] 에서 다음 점까지의 방향을 나타내는 단위벡터
	vector<vector2> toNext(n);
	for(int i = 0; i < n; i++)
		toNext[i] = (p[(i+1) % n] - p[i]).normalize();

	// a 와 b 는 각각 두 선분이 어디에 붙은 채로 회전하고 있는가를 나타낸다
	int a = left, b = right;
	// 반 바퀴 돌아서 두 선분이 서로 위치를 바꿀 때까지 계속한다
	while(a != right || b != left) {
		// a 에서 다음 점까지의 각도와 b 에서 다음 점까지의 각도 중 어느 쪽이 작은가 확인
		double cosThetaA = calipersA.dot(toNext[a]);
		double cosThetaB = -calipersA.dot(toNext[b]);
		if(cosThetaA > cosThetaB) { // thetaA < thetaB
			calipersA = toNext[a];
			a = (a + 1) % n;
		}
		else {
			calipersA = -toNext[b];
			b = (b + 1) % n;
		}
		ret = max(ret, (p[a] - p[b]).norm());
	}
	return ret;
}

// (a,b,c) 가 그리는 삼각형의 넓이
double area(const vector2& a, const vector2& b, const vector2& c) {
	return fabs((b-a).cross(c-a)) / 2.0;
}

// 볼록 다각형 지름을 구하는 Shamos 알고리즘
double diameter2(const polygon& p) {

	int n = p.size();
	int b = 1;
	double ret = 0;
	for(int a = 0; a < n; ++a) {
		while(area(p[(b+1)%n], p[a], p[(a+1)%n]) > area(p[b], p[a], p[(a+1)%n]))
			b = (b+1) % n;
		ret = max(ret, (p[a] - p[b]).norm());
	}
	return ret;
}

typedef vector<vector2> polygon;

// points 에 있는 점들을 모두 포함하는 최소의 볼록 다각형을 찾는다.
// 볼록 다각형의 꼭지점은 제일 왼쪽 아래 점부터 시작해서 반시계 방향으로 반환된다.
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

void testPoly(const polygon& p) {
	polygon hull = giftWrap(p);
	double brute = 0;
	for(int i = 0; i < hull.size(); i++)
		for(int j = 0; j < i; j++)
			brute = max(brute, (hull[i] - hull[j]).norm());
	assert(fabs(brute - diameter(hull)) < 1e-8);
	if(fabs(brute - diameter2(hull)) > 1e-8) {
		printf("damn\n");
		diameter2(hull);
		assert(false);

	}
	//printf("PASS %.10lf\n", brute);
}

int main() {
	vector<vector2> points;
	points.push_back(vector2(0,0));
	points.push_back(vector2(1,0));
	points.push_back(vector2(0,2));
	points.push_back(vector2(-1,0));
	testPoly(points);
	points.clear();
	points.push_back(vector2(0,0));
	points.push_back(vector2(1,0));
	points.push_back(vector2(1,1)); testPoly(points);
	points.push_back(vector2(0,1)); testPoly(points);
	points.push_back(vector2(0,1)); testPoly(points);
	points.push_back(vector2(0.5,0.5)); testPoly(points);
	points.push_back(vector2(1.5,0.5)); testPoly(points);
	points.push_back(vector2(1.5,2)); testPoly(points);
	points.push_back(vector2(2,1)); testPoly(points);
	points.push_back(vector2(1,2)); testPoly(points);


	int TRIALS = 1000000;
	for(int cc = 0; cc < TRIALS; cc++) {
		vector<vector2> points;
		points.push_back(vector2(50,50));
		points.push_back(vector2(51,50));
		points.push_back(vector2(51,51));
		for(int i = 0; i < 50; ++i) {
			int y = rand() % 100, x = rand() % 100;
			points.push_back(vector2(x, y));
			testPoly(points);
		}
		if(cc % 100 == 99) { printf("."); fflush(stdout); }
	}

	printf("\nall good.\n");
}

