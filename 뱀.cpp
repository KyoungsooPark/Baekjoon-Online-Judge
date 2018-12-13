/*
https://www.acmicpc.net/problem/3190
*/

#include <cstdio>
#include <queue>
using namespace std;
typedef struct { int x, y; } snake;

snake s[10001];	// 뱀 이동 시 head와 tail의 인덱스 변경
char ctrl[10001];	// ctrl[t]: 시간 t에서 뱀 방향 전환
int map[102][102];
int dx[4] = { 0, 1, 0, -1 };	// 시계 방향 회전 순서
int dy[4] = { 1, 0, -1, 0 };	// 시계 방향 회전 순서
int N, head, tail, dir, time = 0;
// 뱀 위치, head 및 tail 인덱스 초기화, map의 벽 설정
void init(void) {
	s[0].x = s[0].y = 1;
	head = tail = 0;
	for (int i = 0; i <= N + 1; i++)
		map[0][i] = map[N + 1][i] = map[i][0] = map[i][N + 1] = 1;
}
// 현재 시간 time 에서의 조작 ctrl에 따라 뱀 이동
bool move(void) {
	if (map[s[head].x][s[head].y] == 1)
		return false;
	map[s[head].x][s[head].y] = 1;
	switch (ctrl[time]) {
	case 'L': dir == 0 ? dir = 3 : dir--; break;	// 왼쪽 (반시계 방향) 회전
	case 'D': dir == 3 ? dir = 0 : dir++; break;	// 오른쪽 (시계 방향) 회전
	}
	int nx = s[head].x + dx[dir], ny = s[head].y + dy[dir];
	switch (map[nx][ny]) {
	case 0:	// 다음 위치에 아무것도 없는 경우 머리, 꼬리 모두 이동
		map[s[tail].x][s[tail].y] = 0, tail++;	// 꼬리 이동 (break 없이 다음 case 수행)
	case 2:	// 다음 위치에 사과가 있는 경우 머리만 이동
		s[++head] = { nx, ny };	// 머리 이동
	}
	return true;
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
	while (move()) time++;
	// 출력부
	printf("%d\n", time);
	return 0;
}
