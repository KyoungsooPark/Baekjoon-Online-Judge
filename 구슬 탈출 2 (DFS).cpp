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
int dx[4] = { 0, 0, 1, -1 };	// 동, 서, 남, 북
int dy[4] = { 1, -1, 0, 0 };	// 동, 서, 남, 북
int N, M, ans = -1;
// 벽에 닿거나 구멍에 빠질 때까지 구슬 이동
void move(ball &b, int d) {
	int nx = b.x, ny = b.y;
	while (true) {
		nx += dx[d], ny += dy[d];
		if (map[nx][ny] == '#')	// 벽
			return;
		b.x = nx, b.y = ny;
		if (map[nx][ny] == 'O')	// 구멍
			return;
	}
}

void go(ball R, ball B, int d, int n) {
	if (n > 10)	// 기울이기 10회 초과
		return;
	if (ans != -1 && n > ans)	// 
		return;
	ball nR = R, nB = B;
	move(nR, d), move(nB, d);	// 구슬 이동
	if (map[nB.x][nB.y] == 'O')	// 파란 구슬 탈출
		return;
	if (map[nR.x][nR.y] == 'O') {	// 빨간 구슬 탈출
		ans = n;	// ans 업데이트
		return;
	}
	if (nR == nB) {	// 두 구슬이 겹친 경우
		switch (d) {
		case 0: R.y < B.y ? nR.y-- : nB.y--; break;
		case 1: R.y < B.y ? nB.y++ : nR.y++; break;
		case 2: R.x < B.x ? nR.x-- : nB.x--; break;
		case 3: R.x < B.x ? nB.x++ : nR.x++; break;
		}
	}
	if (!visited[nR.x][nR.y][nB.x][nB.y]) {	// 방문하지 않은 지점인 경우
		visited[nR.x][nR.y][nB.x][nB.y] = true;	// 방문 표시
		for (int nd = 0; nd < 4; nd++)	// 다음 기울이기 진행
			if (nd != d)
				go(nR, nB, nd, n + 1);
		visited[nR.x][nR.y][nB.x][nB.y] = false;	// 방문 표시 해제
	}
}

int main(void) {
	// 입력부
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
	// 처리부
	visited[R.x][R.y][B.x][B.y] = true;	// 시작 지점 방문 표시
	for (int d = 0; d < 4; d++)	// 시작 지점으로부터 네 방향 기울이기 탐색
		go(R, B, d, 1);
	// 출력부
	printf("%d\n", ans);
	return 0;
}