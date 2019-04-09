/*
https://www.acmicpc.net/problem/17070
*/

#include <cstdio>
using namespace std;

int map[16][16];
int dx[3] = { 0, 1, 1 };	// →, ↘, ↓
int dy[3] = { 1, 1, 0 };	// →, ↘, ↓
int N, ans = 0;
// 현재 위치(x, y) 및 방향(d)으로부터 다음 위치 및 방향 dfs 및 이동
void go(int x, int y, int d) {
	if (x == N - 1 && y == N - 1) {
		ans++;
		return;
	}
	int nx = x + 1, ny = y + 1;
	switch (d) {
	case 0:	// →
		if (ny < N && !map[x][ny]) {
			go(x, ny, 0);	// →
			if (nx < N && !map[nx][y] && !map[nx][ny])
				go(nx, ny, 1);	// ↘
		}
		break;
	case 1:	// ↘
			// →, ↘, ↓
		if (ny < N && !map[x][ny]) {
			go(x, ny, 0);	// →
			if (nx < N && !map[nx][y] && !map[nx][ny])
				go(nx, ny, 1);	// ↘
		}
		if (nx < N && !map[nx][y])
			go(nx, y, 2);	// ↓
		break;
	case 2:	// ↓
		if (nx < N && !map[nx][y]) {
			go(nx, y, 2);	// ↓
			if (ny < N && !map[x][ny] && !map[nx][ny])
				go(nx, ny, 1);	// ↘
		}
	}
}

int main(void) {
	// 입력부
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &map[i][j]);
	// 처리부
	go(0, 1, 0);
	// 출력부
	printf("%d\n", ans);
}
