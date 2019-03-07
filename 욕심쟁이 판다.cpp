/*
https://www.acmicpc.net/problem/1937
*/

#include <cstdio>
using namespace std;
int map[500][500];	// 대나무 숲 정보
int check[500][500];	// check[x][y]: 좌표 (x, y)에서 방문할 수 있는 최대 깊이
int dx[4] = { 0, 0, 1, -1 };	// 동, 서, 남, 북
int dy[4] = { 1, -1, 0, 0 };	// 동, 서, 남, 북
int N, ans = 0;

int max(int a, int b) { return a >= b ? a : b; }
// 주변을 탐색하며 좌표 (x, y)에서 방문할 수 있는 최대 깊이 업데이트 및 반환
int go(int x, int y) {
	if (check[x][y])	// 이미 검사하여 check[x][y]에 정보가 존재하는 경우
		return check[x][y];	// 해당 정보 반환

	bool flag = false;	// 주변의 방문 가능 지점 유무를 검사하기 위한 flag
	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d], ny = y + dy[d];
		if (0 <= nx && nx < N && 0 <= ny && ny < N) {
			if (map[nx][ny] > map[x][y]) {	// 방문 가능 지점인 경우
				flag = true;	// flag set
				// 현재 정보와 해당 지점 탐색 정보 비교 및 업데이트
				check[x][y] = max(check[x][y], go(nx, ny) + 1);
			}
		}
	}
	if (!flag)	// 방문 가능 지점이 존재하지 않는 경우
		return check[x][y] = 1;	// 현재 지점의 깊이를 1로 설정 후 반환
	return check[x][y];	// 탐색 결과 반환
}

int main(void) {
	// 입력부
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &map[i][j]);
	// 처리부
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (!check[i][j])
				ans = max(ans, go(i, j));
	// 출력부
	printf("%d\n", ans);
	return 0;
}