/*
https://www.acmicpc.net/submit/11048
*/

#include <cstdio>
using namespace std;

int map[1001][1001];
int d[1001][1001];

int max(int a, int b) { return a >= b ? a : b; }

int main(void) {
	int N, M;
	// 입력부
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			scanf("%d", &map[i][j]);
	// 처리부
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			d[i][j] = max(d[i - 1][j], d[i][j - 1]) + map[i][j];
	// 출력부
	printf("%d\n", d[N][M]);
	return 0;
}
