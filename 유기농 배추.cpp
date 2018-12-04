/*
https://www.acmicpc.net/problem/1012
*/

#include <cstdio>
#include <cstring>
using namespace std;

bool map[50][50], check[50][50];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int N, M, K;

void go(int x, int y) {
	check[x][y] = true;
	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d], ny = y + dy[d];
		if (0 <= nx && nx < N && 0 <= ny && ny < M) {
			if (map[nx][ny] && !check[nx][ny])
				go(nx, ny);
		}
	}
}

int main(void) {
	int T;
	scanf("%d", &T);
	while (T--) {
		int ans = 0;
		// 입력부
		scanf("%d %d %d", &M, &N, &K);
		for (int k = 0; k < K; k++) {
			int x, y;
			scanf("%d %d", &y, &x);
			map[x][y] = true;
		}

		// 처리부
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				// check 되지 않은 배추가 존재하면
				if (map[i][j] && !check[i][j]) {
					ans++;	// 군집 수 증가
					go(i, j);	// 해당 군집 내 모든 배추 check
				}
			}
		}
		memset(map, false, sizeof(map));
		memset(check, false, sizeof(check));

		// 출력부
		printf("%d\n", ans);
	}
	return 0;
}