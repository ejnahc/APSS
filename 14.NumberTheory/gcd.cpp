int gcd(int p, int q) {
	if (q == 0) return p;
	return gcd(q, p % q);
}

int g(int x, int y) {
	while(x%y)x^=y^=x^=y%=x;
	return y;
}