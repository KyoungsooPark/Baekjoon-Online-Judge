/*
https://www.acmicpc.net/problem/13458
*/

#include <cstdio>
#define MAX	1000000
using namespace std;

int map[MAX + 1];

int main(void) {
	int N, B, C;
	unsigned long long ans = 0;
	// 입력부
	scanf("%d", &N);
	for (int n = 0; n < N; n++)
		scanf("%d", &map[n]);
	scanf("%d %d", &B, &C);

	// 처리부
	for (int n = 0; n < N; n++) {
		map[n] -= B;
		ans++;
		if (map[n] <= 0)
			continue;
		if (map[n] % C)
			ans += map[n] / C + 1;
		else
			ans += map[n] / C;
	}

	// 출력부
	printf("%llu\n", ans);	// unsigne long long 출력
	return 0;
}