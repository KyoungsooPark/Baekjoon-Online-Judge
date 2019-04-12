/*
https://www.acmicpc.net/problem/13460
*/

#include <cstdio>
#include <queue>
using namespace std;
struct ball { int rx, ry, bx, by; };

queue<ball> q;
bool visited[10][10][10][10];	// visited[rx][ry][bx][by]
char map[10][10];
int dx[4] = { 0, 0, 1, -1 };	// 동, 서, 남, 북
int dy[4] = { 1, -1, 0, 0 };	// 동, 서, 남, 북
int N, M, ans = -1;
// 벽에 닿거나 구멍에 빠질 때까지 구슬 이동
void move(int &x, int &y, int d) {
	int nx = x, ny = y;
	while (true) {
		nx += dx[d], ny += dy[d];
		if (map[nx][ny] == '#')	// 벽
			return;
		x = nx, y = ny;
		if (map[nx][ny] == 'O')	// 구멍
			return;
	}
}

int main(void) {
	int rx, ry, bx, by;
	// 입력부
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			scanf(" %c", &map[i][j]);
			switch (map[i][j]) {
			case 'R': rx = i, ry = j, map[i][j] = '.'; break;
			case 'B': bx = i, by = j, map[i][j] = '.'; break;
			}
		}
	// 처리부
	q.push({ rx, ry, bx, by });
	visited[rx][ry][bx][by] = true;	// 시작 지점 방문 표시
	for (int i = 1; i < 11; i++) {	// 기울이기 최대 10회 수행
		int size = q.size();
		while (size--) {
			ball now = q.front(); q.pop();
			for (int d = 0; d < 4; d++) {	// 네 방향 기울이기 탐색
				rx = now.rx, ry = now.ry;
				bx = now.bx, by = now.by;
				move(rx, ry, d); move(bx, by, d);	// 구슬 이동
				if (map[bx][by] == 'O')	// 파란 구슬 탈출
					continue;
				if (map[rx][ry] == 'O') {	// 빨간 구슬 탈출
					printf("%d\n", i);
					return 0;
				}
				if (rx == bx && ry == by) {	// 두 구슬이 겹친 경우
					switch (d) {
					case 0: now.ry < now.by ? ry-- : by--; break;
					case 1: now.ry < now.by ? by++ : ry++; break;
					case 2: now.rx < now.bx ? rx-- : bx--; break;
					case 3: now.rx < now.bx ? bx++ : rx++; break;
					}
				}
				if (!visited[rx][ry][bx][by]) {
					q.push({ rx, ry, bx, by });
					visited[rx][ry][bx][by] = true;
				}
			}
		}
	}
	// 기울이기 10회 이내 빨간 구슬 탈출 실패
	printf("-1\n");
	return 0;
}