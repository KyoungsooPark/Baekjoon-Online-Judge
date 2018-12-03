/*
https://www.acmicpc.net/problem/1009
*/

#include <cstdio>
using namespace std;

int cal(int base, int index) {
	// 숫자를 곱하며 mod 해주는 것을 n회 반복
	// a^(2n) = (a^n)^2 이라는 점에 착안
	int ret = 1;
	while (index) {
		if (index & 1)
			ret = ret * base % 10;
		base = base * base % 10;
		index >>= 1;
	}
	return ret;
}

int main(void) {
	int T;
	scanf("%d", &T);
	while (T--) {
		int a, b, num;
		// 입력부
		scanf("%d %d", &a, &b);
		// 처리부
		num = cal(a, b);
		num = num == 0 ? 10 : num;
		// 출력부
		printf("%d\n", num);
	}
	return 0;
}