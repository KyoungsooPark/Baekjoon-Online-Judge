/*
https://www.acmicpc.net/problem/3190
*/

#include <cstdio>
#include <queue>
using namespace std;
typedef struct { int x, y; } snake;

snake s[10001];
char ctrl[10001];
int map[102][102];
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };
int N, head, tail, dir, time = 0;

void init(void) {
	map[1][1] = 1;
	s[0].x = s[0].y = 1;
	head = tail = 0;
	for (int i = 0; i <= N + 1; i++)
		map[0][i] = map[N + 1][i] = map[i][0] = map[i][N + 1] = 1;
}
// 현재 시간 time 에서의 조작 ctrl에 따라 뱀 이동
bool move(void) {
	switch (ctrl[time]) {
	case 'L': dir == 0 ? dir = 3 : dir--; break;
	case 'D': dir == 3 ? dir = 0 : dir++; break;
	}
	int nx = s[head].x + dx[dir], ny = s[head].y + dy[dir];
	switch (map[nx][ny]) {
	case 1:
		return false;
	case 0:	// 다음 위치에 아무것도 없는 경우 머리, 꼬리 모두 이동
		map[s[tail].x][s[tail].y] = 0, tail++;	// 꼬리 이동
	case 2:	// 다음 위치에 사과가 있는 경우 머리만 이동
		map[nx][ny] = 1, s[++head] = { nx, ny };	// 머리 이동
		return true;
	}
}

int main(void) {
	int K, L;
	// 입력부
	scanf("%d", &N);
	init();
	scanf("%d", &K);
	while (K--) {
		int x, y;
		scanf("%d %d", &x, &y);
		map[x][y] = 2;
	}
	scanf("%d", &L);
	while (L--) {
		int t; char c;
		scanf("%d %c", &t, &c);
		ctrl[t] = c;
	}
	// 처리부
	while (move()) ++time;
	// 출력부
	printf("%d\n", ++time);
	return 0;
}