/*
https://www.acmicpc.net/problem/13460
*/

#include <cstdio>
#define QUEUESIZE	100
using namespace std;
typedef struct { int rx, ry, bx, by; } node;

node q[QUEUESIZE];
char map[10][10];
bool visited[10][10][10][10];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int begin, end;

bool empty(void) { return begin == end; }
int size(void) { return begin <= end ? end - begin : QUEUESIZE + end - begin; }
void push(node n) { q[end++] = n; if (end == QUEUESIZE) end = 0; }
node pop(void) { node ret = q[begin++]; if (begin == QUEUESIZE) begin = 0; return ret; }

// 벽에 닿거나 구멍에 빠질 때까지 이동
void move(int &x, int &y, int d) {
	while (true) {
		x += dx[d], y += dy[d];
		if (map[x][y] == '#') {
			x -= dx[d], y -= dy[d];
			break;
		}
		else if (map[x][y] == 'O')
			break;
	}
}

int main(void) {
	int N, M, rx, ry, bx, by, ans = -1;
	
	// 입력부
	scanf("%d %d", &N, &M);
	for (int n = 0; n < N; n++) {
		scanf("%s", &map[n]);
		for (int m = 0; m < M; m++) {
			if (map[n][m] == 'R')
				map[n][m] = '.', rx = n, ry = m;
			else if (map[n][m] == 'B')
				map[n][m] = '.', bx = n, by = m;
		}
	}

	// 처리부
	push({ rx, ry, bx, by });
	visited[rx][ry][bx][by] = true;
	for (int i = 0; i <= 10; i++) {
		int qsize = size();
		while (qsize--) {
			node now = pop();
			if (map[now.rx][now.ry] == 'O') {
				ans = i;
				break;
			}
			for (int d = 0; d < 4; d++) {
				rx = now.rx, ry = now.ry;
				bx = now.bx, by = now.by;
				move(rx, ry, d), move(bx, by, d);

				if (map[bx][by] == 'O')
					continue;
				// 이동 후의 빨간 구슬과 파란 구슬의 위치가 겹쳐진 경우
				if (rx == bx && ry == by) {
					// 이동 전 두 구슬의 위치를 비교하여 이동 후의 위치를 수정
					switch (d) {
					case 0:	now.rx < now.bx ? bx++ : rx++; break;
					case 1:	now.rx < now.bx ? rx-- : bx--; break;
					case 2:	now.ry < now.by ? by++ : ry++; break;
					case 3:	now.ry < now.by ? ry-- : by--; break;
					}
				}
				if (!visited[rx][ry][bx][by]) {
					push({ rx, ry, bx, by });
					visited[rx][ry][bx][by] = true;
				}
			}
		}
		if (ans != -1)
			break;
	}

	// 출력부
	printf("%d\n", ans);
	
	return 0;
}