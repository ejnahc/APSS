// 시계 반대 방향으로 주어진 볼록 다각형에서 가장 먼 꼭지점 쌍 사이의 거리를 반환한다
double diamater(const polygon& p) {
	int n = p.size();

	// 우선 가장 왼쪽에 있는 점과 오른쪽에 있는 점을 찾는다
	int left = min_element(p.begin(), p.end()) - p.begin();
	int right = max_element(p.begin(), p.end()) - p.begin();

	// p[left]와 p[right]에 각각 수직선을 붙인다
	// 두 수직선은 서로 정반대 방향을 가리키므로, A의 방향만을 표현하면 된다
	vector2 calipersA(0, 1);
	double ret = (p[right] - p[left]).norm();

	// toNext[i] = p[i]에서 다음 점까지의 방향을 나타내는 단위 벡터
	vector<vector2> toNext(n);
	for (int i=0; i<n; ++i)
		toNext[i] = (p[(i+1)%n] - p[i]).normalize();

	// a와 b는 각각 두 선분이 어디에 붙은 채로 회전하고 있는지를 나타낸다
	int a = left, b = right;
	// 반 바퀴 돌아서 두 선분이 서로 위치를 바꿀 때까지 계속한다
	while (a != right || b != left) {
		// a에서 다음 점까지의 각도와 b에서 다음 점까지의 각도 중 어느 쪽이 작은지 확인
		double cosThetaA = calipersA.dot(toNext[a]);
		double cosThetaB = -calipersA.dot(toNext[b]);

		if (cosThetaA > cosThetaB) { // thetaA < thetaB
			calipersA = toNext[a];
			a = (a+1)%n;
		} else {
			calipersA = -toNext[b];
			b = (b+1)%n;
		}

		ret = max(ret, (p[a] - p[b]).norm());
	}

	return ret;
}