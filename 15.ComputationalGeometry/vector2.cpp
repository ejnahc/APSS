const double PI = 2.0 * acos(0.0);

// 2차원 벡터의 표현
struct vector2 {
	double x, y;

	explicit vector2(double x_ = 0, double y_ = 0) : x(_x), y(_y) { }

	// 두 벡터의 비교
	bool operator == (const vector2& rhs) const {
		return x == rhs.x && y == rhs.y;
	}

	bool operator < (const vector2& rhs) const {
		return x != rhs.x ? x < rhs.x : y < rhs.y;
	}

	// 벡터의 덧셈과 뺄셈
	vector2 operator + (const vector2& rhs) const {
		return vector2(x + rhs.x, y + rhs.y);
	}

	vector2 operator - (const vector2& rhs) const {
		return vector2(x - rhs.x, y - rhs.y);
	}

	// 실수로 곱셈
	vector2 operator * (double rhs) const {
		return vector2(x * rhs, y * rhs);
	}

	// 벡터의 길이를 반환한다
	double norm() const { return hypot(x, y); }

	// 방향이 같은 단위 벡터(normal vector)를 반환한다
	// 영백터에 대해 호출한 경우 반환 값은 정의되지 않는다
	vector2 normalize() const {
		return vector2(x / norm(), y / norm());
	}

	// x축의 양의 방향으로부터 이 벡터까지 반시계방향으로 잰 각도
	double polar() const {
		return fmod(atan2(y, x) + 2*PI, 2*PI);
	}

	// 내적/외적의 구현
	double dot(const vector2& rhs) const {
		return x * rhs.x + y * rhs.y;
	}

	double cross(const vector2& rhs) const {
		return x * rhs.y - rhs.x * y;
	}

	// 이 벡터를 rhs에 사영한 결과
	vector2 project(const vector2& rhs) const {
		vector2 r = rhs.normalize();
		return r * r.dot(*this);
	}
};

// 세 개의 점 p, a, b가 주어졌을 때 a가 b보다 p에 얼마나 더 가까운지 반환하는 함수
double howMuchCloser(vector p, vector a, vector b) {
	return (b - p).norm() - (a - p).norm();
}

// 원점에서 벡터 b가 백터 a의 반시계방향이면 양수, 시계 방향이면 음수, 평행이면 0을 반환한다
double ccw(vector2 a, vector2 b) {
	return a.cross(b);
}

// 점 p를 기준으로 벡터 b가 벡터 a의 반시계방향일 경우 양수, 시계 방향이면 음수, 평행이면 0을 반환
double ccw(vector2 p, vector2 a, vector2 b) {
	return ccw(a-p, b-p);
}

// (a, b)를 포함하는 선과 (c, d)를 포함하는 선의 교점을 x에 반환한다
// 두 선이 평행이면 (겹치는 경우 포함) 거짓을, 아니면 참을 반환한다
bool lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& x) {
	double det = (b - a).cross(d - c);
	// 두 선이 평행인경우
	if (fabs(det) < EPSILON) return false;

	x = a + (b - a) * ((c - a).cross(d - c) / det);
	return true;
}

// (a, b)와 (c, d)가 평행한 두 선분일 때 이들이 한 점에서 겹치는지 확인한다
bool parallelSegments(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p) {
	if (b < a) swap(a, b);
	if (d < c) swap(c, d);

	// 한 직선 위에 없거나 두 선분이 겹치지 않는 경우를 우선 걸러낸다
	if (ccw(a, b, c) != 0 || b < c || d < a) return false;

	// 두 선분이 확실히 겹친다. 교차점을 하나 찾는다
	if (a < c) p = c; else p = a;

	return true;
}

// p가 (a, b)를 감싸면서 각 변이 x, y축에 평행한 최소 사각형 내부에 있는지 확인한다
// a, b, p는 일직선 상에 있다고 가정한다
bool inBoundingRectangle(vector2 p, vector2 a, vector2 b) {
	if (b < a) swap(a, b);
	return p == a || p == b || (a < p && p < b);
}

// (a, b) 선분과 (c, d) 선분의 교점을 p에 반환한다
// 교점이 여러개일 경우 아무 점이나 반환한다
// 두 선분이 교차하지 않을 경우 false를 반환한다
bool segmentIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p) {
	// 두 직선이 평행인 경우 예외 처리
	if (!lineIntersection(a, b, c, d, p))
		return parallelSegments(a, b, c, d, p);

	// p가 두 선분에 포함되어 있는 경우에만 참을 반환한다
	return inBoundingRectangle(p, a, b) && inBoundingRectangle(p, c, d);
}

// 두 선분이 서로 접촉하는지 여부를 판단한다
bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d) {
	double ab = ccw(a, b, c) * ccw(a, b, d);
	double cd = ccw(c, d, a) * ccw(c, d, b);

	// 두 선분이 한 직선 위에 있거나 끝점이 겹치는 경우
	if (ab == 0 && cd == 0) {
		if (b < a) swap(a, b);
		if (d < c) swap(c, d);

		return !(b < c || d < a);
	}

	return ab <= 0 && cd <= 0;
}

// 점 p에서 (a, b) 직선에 내린 수선의 발을 구한다
vector2 perpendicularFoot(vector2 p, vector2 a, vector2 b) {
	return a + (p - a).project(b - a);
}

// 점 p와 (a, b) 직선 사이의 거리를 구한다
double pointToLine(vector2 p, vector2 a, vector2 b) {
	return (p - perpendicularFoot(p, a, b)).norm();
}

// here에 있던 공이 dir 방향으로 굴러와 center를 중심으로 하는 장애물에서
// contact 위치에서 충돌했을 때 공의 새로운 방향을 반환한다 (p.536)
vector2 reflect(vector2 dir, vector2 center, vector2 contact) {
	return (dir - dir.reflect(contact - center) * 2).normalize();
}

// 주어진 단순 다각형 p의 넓이를 구한다
// p는 각 꼭지점의 위치 벡터의 집합으로 주어진다
double area(const vector<vector2>& p) {
	double ret = 0;
	for (int i=0; i<p.size(); ++i) {
		int j = (i + 1) % p.size();
		ret += p[i].x * p[j].y - p[j].x * p[i].y;
	}

	return fabs(ret) / 2.0;
}

// 점 q가 다각형 p 안에 포함되어 있을 경우 참, 아닌 경우 거짓을 반환한다
// q가 다각형의 경계 위에 있는 경우의 반환 값은 정의되어 있지 않다
bool isInside(vector2 q, const vector<vector2>& p) {
	int crosses = 0;
	for (int i=0; i<p.size(); ++i) {
		int j = (i + 1) % p.size();

		// (p[i], p[j])가 반직선을 세로로 가로지르는가?
		if ((p[i].y > q.y) != (p[j].y > q.y)) {
			// 가로지르는 x 좌표를 계산한다
			double atX = (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y) + p[i].x;
			if (q.x < atX)
				++crosses;
		}
	}

	return crosses % 2 > 0;
}


typedef vector<vector2> polygon;
// 반평면과 단순 다각형의 교집합을 구한다
// (a, b)를 포함하는 직선으로 다각형 p를 자른 뒤, (a, b)의 왼쪽에 있는 부분들을 반환한다
polygon cutPoly(const polygon& p, const vector2& a, const vector2& b) {
	int n = p.size();
	// 각 점이 반평면 내에 있는지 여부를 우선 확인한다
	vector<bool> inside(n);
	for (int i=0; i<n; ++i) {
		inside[i] = ccw(a, b, p[i]) >= 0;
	}

	polygon ret;
	// 다각형의 각 변을 순회하면서 결과 다각형의 각 점을 발견한다
	for (int i=0; i<n; ++i) {
		int j = (i+1) % n;
		// 반평면 내에 있는 점 p[i]는 항상 결과 다각형에 포함된다
		if (inside[i]) ret.push_back(p[i]);
		// 변 p[i]-p[j]가 직선과 교차하면 교차점을 결과 다각형에 포함시킨다
		if (inside[i] != inside[j]) {
			vector2 cross;
			assert(lineIntersection(p[i], p[j], a, b, cross));
			ret.push_back(cross);
		}
	}

	return ret;
}

// 서덜랜드-호지렌(Surtherland-Hodgman) 알고리즘을 이용한 다각형 클리핑
polygon intersection(const polygon& p, double x1, double y1, double x2, double y2) {
	vector2 a(x1, y1), b(x2, y1), c(x2, y2), d(x1, y2);
	polygon ret = cutPoly(p, a, b);
	ret = cutPoly(ret, b, c);
	ret = cutPoly(ret, c, d);
	ret = cutPoly(ret, d, a);

	return ret;
}


// points에 있는 점들을 모두 포함하는 최소의 볼록 다각형을 찾는다
polygon giftWrap(const vector<vector2>& points) {
	int n = points.size();
	polygon hull;

	// 가장 왼쪽 아래점을 찾는다. 이 점은 껍질에 반드시 포함된다
	vector2 pivot = *min_element(points.begin(), points.end());
	hull.push_back(pivot);

	while (true) {
		// ph에서 시작하는 벡터가 가장 왼쪽인 점 next를 찾는다
		// 평행인 점이 여러 개 있으면 가장 먼 것을 선택한다
		vector2 ph = hull.back(), next = points[0];

		for (int i=1; i<n; ++i) {
			double cross = ccw(ph, next, points[i]);
			double dist = (next - ph).norm() - (points[i] - ph).norm();

			if (cross > 0 || (cross == 0 && dist < 0))
				next = points[i];
		}

		// 시작점으로 돌아왔으면 종료한다
		if (next == pivot) break;

		// next를 블록 껍질에 포함시킨다
		hull.push_back(next);
	}

	return hull;
}

// 두 다각형이 서로 닿거나 겹치는지 여부를 판단한다. 한 점이라도 겹친다면 true를 반환한다
bool polygonIntersects(const polygon& p, const polygon& q) {
	int n = p.size(), m = q.size();
	// 우선 한 다각형이 다른 다각형에 포함되어 있는 경우를 확인한다
	if (isInside(p[0], q) || isInside(q[0], p)) return true;
	// 이 외의 경우, 두 다각형이 서로 겹친다면 서로 닿는 두 면이 반드시 존재한다
	for (int i=0; i<n; ++i)
		for (int j=0; j<m; ++j)
			if (segmentIntersects(p[i], p[(i+1)%n], q[j], q[(j+1)%m]))
				return true;

	return false;
}