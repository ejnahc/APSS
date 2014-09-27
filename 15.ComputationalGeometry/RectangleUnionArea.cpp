// x1 < x2, y1 < y2
struct Rectangle {
	int x1, x2, y1, y2;
};

// 직사각형들의 면적을 계산한다
int unionArea(const vector<Rectangle>& rects) {
	if (rects.empty()) return 0;

	// 이벤트 정보: (x 좌표, 왼쪽인지 오른쪽인지, 사각형의 번호)
	typedef pair<int,pair<int, int> > Event;

	vector<Event> events;
	vector<int> ys;

	// 각 사각형을 순회하면서 y 좌표의 모음과 이벤트의 집합을 찾는다
	for (int i=0; i<rects.size(); ++i) {
		ys.push_back(rects[i].y1);
		ys.push_back(rects[i].y2);
		events.push_back(Event(rects[i].x1, make_pair(1, i)));
		events.push_back(Event(rects[i].x2, make_pair(-1, i)));
	}

	// y 좌표의 집합을 정렬하고 중복을 제거
	sorts(ys.begin(), ys.end());
	ys.erase(unique(ys.begin(), ys.end()), ys.end());

	// 이벤트 목록을 정렬
	sort(events.begin(), events.end());

	int ret = 0;
	// count[i] = ys[i] ~ ys[i+1] 구간에 겹쳐진 사각형의 수
	vector<int> count(ys.size()-1, 0);

	for (int i=0; i<events.size(); ++i) {
		int x = events[i].first, delta = events[i].second.first;
		int rectangle = events[i].second.second;

		// count[]를 갱신
		int y1 = rects[rectangle].y1, y2 = rects[rectangle].y2;
		for (int j=0; j<ys.size(); ++j) {
			if (y1 <= ys[j] && ys[j] < y2)
				count[j] += delta;
		}

		// cutLength 값을 갱신한다
		int cutLength = 0;
		for (int j=0; j<ys.size()-1; ++j) {
			if (count[j] > 0)
				cutLength += ys[j+1] - ys[j];
		}

		// 다음 이벤트까지의 거리에 cutLength를 곱한 값을 ret에 더한다
		if (i + 1 < events.size())
			ret += cutLength * (events[i+1].first - x);
	}

	return ret;
}