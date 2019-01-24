/*
https://www.acmicpc.net/problem/1890
*/

#include <cstdio>
using namespace std;

int map[101][101];
long long d[101][101];

int main(void) {
	int N;
	// 입력부
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			scanf("%d", &map[i][j]);
	// 처리부
	d[1][1] = 1;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			// 경로가 없는 위치 또는 목적지인 경우
			if (!d[i][j] || (i == N && j == N))
				continue;
			int down = i + map[i][j];
			int right = j + map[i][j];
			if (down <= N)
				d[down][j] += d[i][j];
			if (right <= N)
				d[i][right] += d[i][j];
		}
	}
	// 출력부
	printf("%lld\n", d[N][N]);
	return 0;
}