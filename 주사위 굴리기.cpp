/*
https://www.acmicpc.net/problem/14499
*/

#include <cstdio>
using namespace std;

int map[20][20], dir[1000], cube[6];
int dx[5] = { 0, 0, 0, -1, 1 };
int dy[5] = { 0, 1, -1, 0, 0 };
int TOP = 0, FRONT = 1, BOTTOM = 2, BACK = 3, LEFT = 4, RIGHT = 5;
int N, M, x, y, K;

void update(void) { map[x][y] ? cube[BOTTOM] = map[x][y], map[x][y] = 0 : map[x][y] = cube[BOTTOM]; }

void move(int d) {
	int nx = x + dx[d], ny = y + dy[d];
	// 이동 가능 위치인 경우만 진행
	if (0 <= nx && nx < N && 0 <= ny && ny < M) {
		int temp = TOP;
		// 방향에 따라 인덱스 업데이트
		// 동, 서: FRONT, BACK 고정
		// 남, 북: LEFT, RIGHT 고정
		switch (d) {
		case 1: TOP = LEFT, LEFT = BOTTOM, BOTTOM = RIGHT, RIGHT = temp; break;
		case 2: TOP = RIGHT, RIGHT = BOTTOM, BOTTOM = LEFT, LEFT = temp; break;
		case 3: TOP = FRONT, FRONT = BOTTOM, BOTTOM = BACK, BACK = temp; break;
		case 4: TOP = BACK, BACK = BOTTOM, BOTTOM = FRONT, FRONT = temp; break;
		}
		x = nx, y = ny;
		update();
		printf("%d\n", cube[TOP]);
	}
}

int main(void) {
	// 입력부
	scanf("%d %d %d %d %d", &N, &M, &x, &y, &K);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			scanf("%d", &map[i][j]);
	for (int i = 0; i < K; i++)
		scanf("%d", &dir[i]);

	// 처리부
	for (int i = 0; i < K; i++)
		move(dir[i]);
	return 0;
}