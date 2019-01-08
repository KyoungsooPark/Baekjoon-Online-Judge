/*
https://www.acmicpc.net/problem/14499
*/

#include <cstdio>
using namespace std;
enum { TOP, BOTTOM, LEFT, RIGHT, FRONT, BACK };
int map[20][20], cube[6], *ptr[6];
int dx[5] = { 0, 0, 0, -1, 1 };
int dy[5] = { 0, 1, -1, 0, 0 };
int N, M, x, y, K;

void move(int d) {
	int nx = x + dx[d], ny = y + dy[d];
	int *temp = ptr[TOP];
	if (nx < 0 || N <= nx || ny < 0 || M <= ny)	// map을 넘어갈 경우
		return;	// 해당 명령 및 출력 무시
	switch (d) {
	case 1:	// 동
		ptr[TOP] = ptr[LEFT];
		ptr[LEFT] = ptr[BOTTOM];
		ptr[BOTTOM] = ptr[RIGHT];
		ptr[RIGHT] = temp;
		break;
	case 2:	// 서
		ptr[TOP] = ptr[RIGHT];
		ptr[RIGHT] = ptr[BOTTOM];
		ptr[BOTTOM] = ptr[LEFT];
		ptr[LEFT] = temp;
		break;
	case 3:	// 북
		ptr[TOP] = ptr[FRONT];
		ptr[FRONT] = ptr[BOTTOM];
		ptr[BOTTOM] = ptr[BACK];
		ptr[BACK] = temp;
		break;
	case 4:	// 남
		ptr[TOP] = ptr[BACK];
		ptr[BACK] = ptr[BOTTOM];
		ptr[BOTTOM] = ptr[FRONT];
		ptr[FRONT] = temp;
		break;
	}
	if (map[nx][ny]) {	// 이동한 칸에 쓰여 있는 수가 0이 아니면
		*ptr[BOTTOM] = map[nx][ny];	// 칸에 쓰여 있는 수가 주사위의 바닥면으로 복사
		map[nx][ny] = 0;	// 칸에 쓰여 있는 수는 0이 됨
	}
	else	// 이동한 칸에 쓰여 있는 수가 0이면
		map[nx][ny] = *ptr[BOTTOM];	// 주사위의 바닥면에 쓰여 있는 수가 칸에 복사
	printf("%d\n", *ptr[TOP]);	// 이동할 때마다 주사위의 윗 면에 쓰여 있는 수 출력
	x = nx, y = ny;	// 주사위 위치 변경
}

int main(void) {
	for (int i = 0; i < 6; i++)
		ptr[i] = &cube[i];
	scanf("%d %d %d %d %d", &N, &M, &x, &y, &K);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			scanf("%d", &map[i][j]);

	while (K--) {
		int d;
		scanf("%d", &d);
		move(d);
	}
	return 0;
}
