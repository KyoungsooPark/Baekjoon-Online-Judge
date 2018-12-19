/*
https://www.acmicpc.net/problem/14500
*/

#include <cstdio>
using namespace std;

int map[500][500];
int N, M, ans = 0;

int max(int a, int b) { return a >= b ? a : b; }
// 1 x 4
int onebyfour(int x, int y) { return y + 3 >= M ? -1 : map[x][y] + map[x][y + 1] + map[x][y + 2] + map[x][y + 3]; }
// 4 x 1
int fourbyone(int x, int y) { return x + 3 >= N ? -1 : map[x][y] + map[x + 1][y] + map[x + 2][y] + map[x + 3][y]; }
// 2 x 2
int twobytwo(int x, int y) { return x + 1 >= N || y + 1 >= M ? -1 : map[x][y] + map[x][y + 1] + map[x + 1][y] + map[x + 1][y + 1]; }
// 2 x 3
int twobythree(int x, int y) {
	return x + 1 >= N || y + 2 >= M ? -1 :
		max(
			map[x][y] + map[x + 1][y] + map[x + 1][y + 1] + map[x + 1][y + 2],
			max(
				map[x][y + 2] + map[x + 1][y] + map[x + 1][y + 1] + map[x + 1][y + 2],
				max(
					map[x][y] + map[x][y + 1] + map[x][y + 2] + map[x + 1][y],
					max(
						map[x][y] + map[x][y + 1] + map[x][y + 2] + map[x + 1][y + 2],
						max(
							map[x][y] + map[x][y + 1] + map[x + 1][y + 1] + map[x + 1][y + 2],
							max(
								map[x][y + 1] + map[x][y + 2] + map[x + 1][y] + map[x + 1][y + 1],
								max(
									map[x][y + 1] + map[x + 1][y] + map[x + 1][y + 1] + map[x + 1][y + 2],
									map[x][y] + map[x][y + 1] + map[x][y + 2] + map[x + 1][y + 1])))))));
}
// 3 x 2
int threebytwo(int x, int y) {
	return x + 2 >= N || y + 1 >= M ? -1 :
		max(
			map[x][y] + map[x + 1][y] + map[x + 2][y] + map[x + 2][y + 1],
			max(
				map[x][y + 1] + map[x + 1][y + 1] + map[x + 2][y] + map[x + 2][y + 1],
				max(
					map[x][y] + map[x][y + 1] + map[x + 1][y + 1] + map[x + 2][y + 1],
					max(
						map[x][y] + map[x][y + 1] + map[x + 1][y] + map[x + 2][y],
						max(
							map[x][y + 1] + map[x + 1][y] + map[x + 1][y + 1] + map[x + 2][y],
							max(
								map[x][y] + map[x + 1][y] + map[x + 1][y + 1] + map[x + 2][y + 1],
								max(
									map[x][y] + map[x + 1][y] + map[x + 1][y + 1] + map[x + 2][y],
									map[x][y + 1] + map[x + 1][y] + map[x + 1][y + 1] + map[x + 2][y + 1])))))));
}
int main(void) {
	// 涝仿何
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			scanf("%d", &map[i][j]);
	// 贸府何
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			ans = max(ans, max(onebyfour(i, j), max(fourbyone(i, j), max(twobytwo(i, j), max(twobythree(i, j), threebytwo(i, j))))));
	// 免仿何
	printf("%d\n", ans);
	return 0;
}