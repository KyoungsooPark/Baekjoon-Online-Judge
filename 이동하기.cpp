/*
https://www.acmicpc.net/submit/11048
*/

#include <cstdio>
#include <cstring>
using namespace std;

int map[1001][1001];
int d[1001][1001];

int max(int a, int b) { return a >= b ? a : b; }

int main(void) {
	int N, M;
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			scanf("%d", &map[i][j]);

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			d[i][j] = max(d[i - 1][j], d[i][j - 1]) + map[i][j];

	printf("%d\n", d[N][M]);
	return 0;
}