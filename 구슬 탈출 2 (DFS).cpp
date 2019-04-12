/*
https://www.acmicpc.net/problem/13460
*/

#include <cstdio>
using namespace std;
struct ball {
	int x, y;
	bool operator==(ball b) { return x == b.x && y == b.y; }
};

ball R, B;
bool visited[10][10][10][10];	// visited[rx][ry][bx][by]
char map[10][10];
int dx[4] = { 0, 0, 1, -1 };	// ��, ��, ��, ��
int dy[4] = { 1, -1, 0, 0 };	// ��, ��, ��, ��
int N, M, ans = -1;
// ���� ��ų� ���ۿ� ���� ������ ���� �̵�
void move(ball &b, int d) {
	int nx = b.x, ny = b.y;
	while (true) {
		nx += dx[d], ny += dy[d];
		if (map[nx][ny] == '#')	// ��
			return;
		b.x = nx, b.y = ny;
		if (map[nx][ny] == 'O')	// ����
			return;
	}
}

void go(ball R, ball B, int d, int n) {
	if (n > 10)	// ����̱� 10ȸ �ʰ�
		return;
	if (ans != -1 && n > ans)	// 
		return;
	ball nR = R, nB = B;
	move(nR, d), move(nB, d);	// ���� �̵�
	if (map[nB.x][nB.y] == 'O')	// �Ķ� ���� Ż��
		return;
	if (map[nR.x][nR.y] == 'O') {	// ���� ���� Ż��
		ans = n;	// ans ������Ʈ
		return;
	}
	if (nR == nB) {	// �� ������ ��ģ ���
		switch (d) {
		case 0: R.y < B.y ? nR.y-- : nB.y--; break;
		case 1: R.y < B.y ? nB.y++ : nR.y++; break;
		case 2: R.x < B.x ? nR.x-- : nB.x--; break;
		case 3: R.x < B.x ? nB.x++ : nR.x++; break;
		}
	}
	if (!visited[nR.x][nR.y][nB.x][nB.y]) {	// �湮���� ���� ������ ���
		visited[nR.x][nR.y][nB.x][nB.y] = true;	// �湮 ǥ��
		for (int nd = 0; nd < 4; nd++)	// ���� ����̱� ����
			if (nd != d)
				go(nR, nB, nd, n + 1);
		visited[nR.x][nR.y][nB.x][nB.y] = false;	// �湮 ǥ�� ����
	}
}

int main(void) {
	// �Էº�
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf(" %c", &map[i][j]);
			switch (map[i][j]) {
			case 'R': R = { i, j }; map[i][j] = '.'; break;
			case 'B': B = { i, j }; map[i][j] = '.'; break;
			}
		}
	}
	// ó����
	visited[R.x][R.y][B.x][B.y] = true;	// ���� ���� �湮 ǥ��
	for (int d = 0; d < 4; d++)	// ���� �������κ��� �� ���� ����̱� Ž��
		go(R, B, d, 1);
	// ��º�
	printf("%d\n", ans);
	return 0;
}