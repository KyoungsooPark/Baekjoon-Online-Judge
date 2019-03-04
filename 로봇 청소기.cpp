/*
https://www.acmicpc.net/problem/14503
*/

#include <cstdio>
using namespace std;

bool map[50][50], check[50][50];
int dx[4] = { -1, 0, 1, 0 };	// 북, 동, 남, 서
int dy[4] = { 0, 1, 0, -1 };	// 북, 동, 남, 서
int N, M, ans = 0;

void go(int x, int y, int d) {
	if (!check[x][y]) {	// 청소하지 않은 경우
		check[x][y] = true;	// 청소
		ans++;	// 청소한 칸 수 증가
	}

	int nx, ny, nd = d;
	for (int i = 0; i < 4; i++) {
		nd == 0 ? nd = 3 : nd--;	// 왼쪽으로 회전
		nx = x + dx[nd], ny = y + dy[nd];	// 회전
		if (!map[nx][ny] && !check[nx][ny]) {	// 벽이 없고 청소하지 않은 경우
			go(nx, ny, nd);	// 해당 위치로 이동
			return;
		}
	}
	nd = (d + 2) % 4;	// 현재 방향의 반대 방향
	nx = x + dx[nd], ny = y + dy[nd];	// 현재 위치의 뒷 칸
	if (!map[nx][ny])	// 뒤에 벽이 없으면
		go(nx, ny, d);	// 한 칸 뒤로 이동, 방향은 유지
}

int main(void) {
	int r, c, d;
	// 입력부
	scanf("%d %d", &N, &M);
	scanf("%d %d %d", &r, &c, &d);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			scanf("%d", &map[i][j]);
	
	// 처리부
	go(r, c, d);

	// 출력부
	printf("%d\n", ans);
	return 0;
}
