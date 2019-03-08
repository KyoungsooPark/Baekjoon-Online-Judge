/*
https://www.acmicpc.net/problem/1937
*/

#include <cstdio>
using namespace std;

int map[500][500];	// 대나무 숲 정보
int check[500][500];	// check[x][y]: 좌표 (x, y)에서 방문 가능한 최대 깊이
int dx[4] = { 0, 0, 1, -1 };	// 동, 서, 남, 북
int dy[4] = { 1, -1, 0, 0 };	// 동, 서, 남, 북
int n, ans = 0;

int max(int a, int b) { return a >= b ? a : b; }
// 주변을 탐색하며 좌표 (x, y)에서 방문 가능한 최대 깊이 업데이트
void go(int x, int y) {
	bool flag = false;	// 주변의 방문 가능 지점 유무를 검사하기 위한 flag
	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d], ny = y + dy[d];
		if (0 <= nx && nx < n && 0 <= ny && ny < n) {	// 탐색 범위 이내
			if (map[x][y] < map[nx][ny]) {	// 방문 가능 지점
				if (!check[nx][ny])	// 해당 방문 가능 지점을 아직 탐색하지 않은 경우
					go(nx, ny);	// 탐색
				check[x][y] = max(check[x][y], check[nx][ny] + 1); // 현재 정보와 탐색 결과 비교 및 업데이트
				flag = true;	// flag set
			}
		}
	}
	if (!flag)	// 방문 가능 지점이 존재하지 않는 경우
		check[x][y] = 1;	// 현재 지점의 깊이를 1로 설정 후 반환
	ans = max(ans, check[x][y]);
}

int main(void) {
	// 입력부
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &map[i][j]);
	// 처리부
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (!check[i][j])
				go(i, j);
	// 출력부
	printf("%d\n", ans);
	return 0;
}