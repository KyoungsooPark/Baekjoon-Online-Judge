/*
https://www.acmicpc.net/problem/15685
*/

#include <cstdio>
using namespace std;

bool map[101][101];
int gen[1024] = { 0, 1, 2, 1, 2, 3, 2, 1 };
int dx[4] = { 0, -1, 0, 1 };
int dy[4] = { 1, 0, -1, 0 };
// 시작 방향이 →(0)인 드래곤 커브의 10세대 까지의 방향(gen) 계산
void init(void) {
	for (int i = 8; i < 1024; )
		for (int j = i - 1; j >= 0; j--, i++)
			gen[i] = gen[j] < 3 ? gen[j] + 1 : 0;
}
// gen을 이용하여 시작 방향에 따른 드래곤 커브 계산
void generate(int x, int y, int d, int g) {
	int dd = d - gen[0];	// gen과의 시작 방향 차이
	map[x][y] = true;
	for (int i = 0; i < (1 << g); i++) {
		int nd = gen[i] + dd;
		if (nd > 3) nd -= 4;
		x += dx[nd], y += dy[nd];
		if (x < 0 || 100 < x || y < 0 || 100 < y)
			break;
		map[x][y] = true;
	}
}
// 네 꼭짓점이 모두 드래곤 커브의 일부인 1×1 크기의 정사각형의 개수 반환
int check(void) {
	int ret = 0;
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			if (map[i][j] && map[i][j + 1] && map[i + 1][j] && map[i + 1][j + 1])
				ret++;
	return ret;
}

int main(void) {
	int N;
	scanf("%d", &N);
	init();
	while (N--) {
		int x, y, d, g;
		scanf("%d %d %d %d", &y, &x, &d, &g);
		generate(x, y, d, g);
	}
	printf("%d\n", check());
	return 0;
}