// 이분법의 예제 구현
double f(double x);

double bisection(double lo, double hi) {
	// 반복문 불변식을 강제한다
	if (f(lo) > 0)
		swap(lo, hi);

	// 반복문 불변식 f(lo) <= 0 < f(hi)
	while (fabs(hi - lo) > 2e-7) {
		double mid = (lo + hi) / 2;
		double fmid = f(mid);

		if (fmid <= 0)
			lo = mid;
		else
			hi = mid;
	}

	// 가운데 값을 정한다
	return (lo + hi) / 2;
}