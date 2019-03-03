/*
https://www.acmicpc.net/problem/14500
*/

#include <cstdio>
using namespace std;

int map[500][500];
int N, M, ans = 0;

int max(int a, int b) { return a >= b ? a : b; }

void calculate(int x, int y) {
	if (y + 3 < M)	// 1 x 4
		ans = max(ans, map[x][y] + map[x][y + 1] + map[x][y + 2] + map[x][y + 3]);
	if (x + 3 < N)	// 4 x 1
		ans = max(ans, map[x][y] + map[x + 1][y] + map[x + 2][y] + map[x + 3][y]);
	if (x + 1 < N && y + 1 < M)	// 2 x 2
		ans = max(ans, map[x][y] + map[x][y + 1] + map[x + 1][y] + map[x + 1][y + 1]);
	if (x + 2 < N && y + 1 < M) {	// 3 x 2
		ans = max(ans, map[x][y] + map[x + 1][y] + map[x + 2][y] + map[x + 2][y + 1]);
		ans = max(ans, map[x][y + 1] + map[x + 1][y + 1] + map[x + 2][y + 1] + map[x + 2][y]);
		ans = max(ans, map[x][y] + map[x][y + 1] + map[x + 1][y + 1] + map[x + 2][y + 1]);
		ans = max(ans, map[x][y + 1] + map[x][y] + map[x + 1][y] + map[x + 2][y]);

		ans = max(ans, map[x][y] + map[x + 1][y] + map[x + 1][y + 1] + map[x + 2][y + 1]);
		ans = max(ans, map[x][y + 1] + map[x + 1][y + 1] + map[x + 1][y] + map[x + 2][y]);

		ans = max(ans, map[x][y] + map[x + 1][y] + map[x + 1][y + 1] + map[x + 2][y]);
		ans = max(ans, map[x][y + 1] + map[x + 1][y + 1] + map[x + 1][y] + map[x + 2][y + 1]);
	}
	if (x + 1 < N && y + 2 < M) {	// 2 x 3
		ans = max(ans, map[x + 1][y] + map[x + 1][y + 1] + map[x + 1][y + 2] + map[x][y + 2]);
		ans = max(ans, map[x + 1][y] + map[x][y] + map[x][y + 1] + map[x][y + 2]);
		ans = max(ans, map[x][y] + map[x + 1][y] + map[x + 1][y + 1] + map[x + 1][y + 2]);
		ans = max(ans, map[x][y] + map[x][y + 1] + map[x][y + 2] + map[x + 1][y + 2]);

		ans = max(ans, map[x + 1][y] + map[x + 1][y + 1] + map[x][y + 1] + map[x][y + 2]);
		ans = max(ans, map[x][y] + map[x][y + 1] + map[x + 1][y + 1] + map[x + 1][y + 2]);

		ans = max(ans, map[x][y] + map[x][y + 1] + map[x + 1][y + 1] + map[x][y + 2]);
		ans = max(ans, map[x + 1][y] + map[x + 1][y + 1] + map[x][y + 1] + map[x + 1][y + 2]);
	}
}

int main(void) {
	// 입력부
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			scanf("%d", &map[i][j]);
	// 처리부
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			calculate(i, j);
	// 출력부
	printf("%d\n", ans);
	return 0;
}
