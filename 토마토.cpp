/*
https://www.acmicpc.net/problem/7576
*/

#include <cstdio>
#include <queue>
using namespace std;
typedef struct { int x, y; } point;

int map[1000][1000];
int dx[4] = { 0, 0, 1, -1 };	// 동, 서, 남, 북
int dy[4] = { 1, -1, 0, 0 };	// 동, 서, 남, 북

int main(void) {
	int N, M, ans = -1;
	queue<point> q;
	// 입력부
	scanf("%d %d", &M, &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 1)
				q.push({ i, j });
		}
	}
	// 처리부
	while (!q.empty()) {
		int size = q.size();
		while (size--) {	// 세대(generation) 단위 수행
			point now = q.front();
			q.pop();
			for (int d = 0; d < 4; d++) {
				int nx = now.x + dx[d], ny = now.y + dy[d];
				if (0 <= nx && nx < N && 0 <= ny && ny < M) {	// 창고 범위를 벗어나지 않을 때
					if (!map[nx][ny]) {	// 익지 않은 토마토가 인접한 경우
						map[nx][ny] = 1;	// 해당 토마토 익음
						q.push({ nx, ny });	// 익은 토마토 위치 큐에 삽입
					}
				}
			}
		}
		ans++;
	}
	// 출력부
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (!map[i][j]) {	// 익지 않은 토마토가 있는 경우
				ans = -1;
				break;
			}
		}
		if (ans == -1)
			break;
	}
	printf("%d\n", ans);
	return 0;
}