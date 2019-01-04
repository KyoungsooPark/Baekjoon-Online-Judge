/*
https://www.acmicpc.net/problem/14503
*/

#include <cstdio>
using namespace std;

bool map[50][50], visited[50][50];
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };
int N, M, ans;

void go(int x, int y, int d) {
	if (!visited[x][y]) {	// 현재 위치 청소 안했으면 청소
		ans++;
		visited[x][y] = true;
	}
	
	for (int i = 0; i < 4; i++) {	// 현재 방향을 기준으로 왼쪽 탐색
		d == 0 ? d = 3 : d--;
		int nx = x + dx[d], ny = y + dy[d];
		if (!map[nx][ny] && !visited[nx][ny]) {	// 청소하지 않은 공간 존재
			go(nx, ny, d);	// 해당 위치로 이동
			return;
		}
	}
	int nd = (d + 2) % 4;
	int nx = x + dx[nd], ny = y + dy[nd];
	if (!map[nx][ny])	// 뒤쪽 방향이 벽이 아니면
		go(nx, ny, d);	// 후진
}

int main(void) {
	// 입력부
	int x, y, d;
	scanf("%d %d", &N, &M);
	scanf("%d %d %d", &x, &y, &d);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			scanf("%d", &map[i][j]);
	// 처리부
	go(x, y, d);
	// 출력부
	printf("%d\n", ans);
	return 0;
}
