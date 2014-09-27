// 비트마스크를 이용한 집합의 구현

// 공집합과 꽉 찬 집합 구하기
int emptyPizza = 0;
int fullPizza = (1 << 20) - 1;

// 원소 추가
toppings |= (1 << p); // 0 <= p < 20

// 원소의 포함 여부 확인
if (toppings & (1 << p)) cout << "pepperoni is in" << endl;

// 원소의 삭제
toppings &= ~(1 << p);

// 원소의 토글
toppings ^= (1 << p);

// 두 집합에 대해 연산하기
int added = (a | b);		// a와 b의 합집합
int intersection = (a & b);	// a와 b의 교집합
int removed = (a & ~b);		// a에서 b를 뺀 차집합
int toggled = (a ^ b);		// a와 b중 하나에만 포함된 원소들의 집합

// 집합의 크기 구하기
// gcc/g++: __builtin_popcount(toppings)
// Visual C++: __popcnt(toppings)
// Java: integer.bitCount(toppings)
int bitCount(int x) {
	if (x == 0) return 0;
	return x % 2 + bitCount(x / 2);
}

// 최소 원소 찾기
// gcc/g++: __builtin_ctz(toppings)
// Visual C++: _BitScanForward(&index, toppings)
// Java: integer.numberOfTrailingZeros(toppings)

// 최하의 비트의 번호 대신 해당 비트를 직접 구하고 싶을 때 (eg: 3 대신 2^3)
int firstTopping = (toppings & -toppings);

// 최소 원소 지우기
toppings &= (toppings - 1);

// 모든 부분 집합 순회하기
for (int subset = pizza; subset; subset = ((subset - 1) & pizza)) {
	// subset은 pizza의 부분 집합
}


// 예제: 15퍼즐 상태 구현하기 (p.587)
typedef unsigned long long uint64;
// mask의 index 위치에 쓰인 값을 반환
int get(uint64 mask, int index) {
	return (mask >> (index << 2)) & 15;
}

// mask의 index위치를 value로 바꾼 결과를 반환
uint64 set(uint64 mask, int index, uint64 value) {
	return mask & ~(15LL << (index << 2)) | (value << (index << 2));
}