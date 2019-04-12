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
int dx[4] = { 0, 0, 1, -1 };	// ��, ��, ��, ��
int dy[4] = { 1, -1, 0, 0 };	// ��, ��, ��, ��
int N, M, ans = -1;
// ���� ��ų� ���ۿ� ���� ������ ���� �̵�
void move(int &x, int &y, int d) {
	int nx = x, ny = y;
	while (true) {
		nx += dx[d], ny += dy[d];
		if (map[nx][ny] == '#')	// ��
			return;
		x = nx, y = ny;
		if (map[nx][ny] == 'O')	// ����
			return;
	}
}

int main(void) {
	int rx, ry, bx, by;
	// �Էº�
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			scanf(" %c", &map[i][j]);
			switch (map[i][j]) {
			case 'R': rx = i, ry = j, map[i][j] = '.'; break;
			case 'B': bx = i, by = j, map[i][j] = '.'; break;
			}
		}
	// ó����
	q.push({ rx, ry, bx, by });
	visited[rx][ry][bx][by] = true;	// ���� ���� �湮 ǥ��
	for (int i = 1; i < 11; i++) {	// ����̱� �ִ� 10ȸ ����
		int size = q.size();
		while (size--) {
			ball now = q.front(); q.pop();
			for (int d = 0; d < 4; d++) {	// �� ���� ����̱� Ž��
				rx = now.rx, ry = now.ry;
				bx = now.bx, by = now.by;
				move(rx, ry, d); move(bx, by, d);	// ���� �̵�
				if (map[bx][by] == 'O')	// �Ķ� ���� Ż��
					continue;
				if (map[rx][ry] == 'O') {	// ���� ���� Ż��
					printf("%d\n", i);
					return 0;
				}
				if (rx == bx && ry == by) {	// �� ������ ��ģ ���
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
	// ����̱� 10ȸ �̳� ���� ���� Ż�� ����
	printf("-1\n");
	return 0;
}