/*
https://www.acmicpc.net/problem/14503
*/

#include <cstdio>
using namespace std;
typedef struct { int x, y, d, c; } cleaner;

cleaner c;
bool map[50][50], visited[50][50];
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };
int N, M, ans;

void move(void) {
	while (true) {
		c.c = 0;
		if (!visited[c.x][c.y]) {	// 현재 위치 청소 안했으면 청소
			ans++;
			visited[c.x][c.y] = true;
		}
		do {	// 현재 방향을 기준으로 왼쪽 탐색
			c.d = c.d == 0 ? 3 : c.d - 1;
			int nx = c.x + dx[c.d], ny = c.y + dy[c.d];
			if (!map[nx][ny] && !visited[nx][ny])
				break;
		} while (++c.c < 4);
		if (c.c < 4) {	// 청소하지 않은 공간 존재
			c.x += dx[c.d], c.y += dy[c.d];	// 해당 위치로 이동
			continue;
		}
		int nd = (c.d + 2) % 4;
		int nx = c.x + dx[nd], ny = c.y + dy[nd];
		if (map[nx][ny])	// 뒤쪽 방향이 벽인 경우 중지
			break;
		c.x = nx, c.y = ny;	// 한 칸 후진
	}
}

int main(void) {
	// 입력부
	scanf("%d %d", &N, &M);
	scanf("%d %d %d", &c.x, &c.y, &c.d);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			scanf("%d", &map[i][j]);
	// 처리부
	move();
	// 출력부
	printf("%d\n", ans);
	return 0;
}