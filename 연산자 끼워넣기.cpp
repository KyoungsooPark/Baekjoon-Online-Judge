#include <cstdio>
using namespace std;

int num[11], nOpt[4], order[10];
int N, max, min;

int calculate(void) {
	// 연산자 우선 순위와 상관없이 왼쪽부터 순서대로 계산
	int ret = num[0];
	for (int n = 1; n < N; n++) {
		switch (order[n - 1]) {
		case 0: ret += num[n]; break;
		case 1: ret -= num[n]; break;
		case 2: ret *= num[n]; break;
		case 3: ret /= num[n]; break;
		}
	}
	return ret;
}

void go(int n) {
	if (n == N - 1) {
		int temp = calculate();
		if (max < temp) max = temp;
		if (min > temp) min = temp;
		return;
	}

	for (int i = 0; i < 4; i++) {
		if (nOpt[i]) {
			order[n] = i;
			nOpt[i]--;
			go(n + 1);
			nOpt[i]++;
		}
	}
}

int main(void) {
	// 입력부
	scanf("%d", &N);
	for (int n = 0; n < N; n++)
		scanf("%d", &num[n]);
	for (int n = 0; n < 4; n++)
		scanf("%d", &nOpt[n]);
	// 처리부
	max = -1e9, min = 1e9;
	go(0);
	// 출력부
	printf("%d\n%d\n", max, min);
	return 0;
}