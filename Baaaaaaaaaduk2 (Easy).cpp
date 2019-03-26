/*
https://www.acmicpc.net/problem/16988
*/

#include <cstdio>
using namespace std;

bool check[20][20];
int map[20][20];
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int N, M, ans = 0;

int max(int a, int b) { return a > b ? a : b; }
bool valid(int x, int y) { return 0 <= x && x < N && 0 <= y && y < M; }

// 상대의 돌과 인접한 위치인지 검사
bool adjacent(int x, int y) {
	if (map[x][y])
		return false;
	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d], ny = y + dy[d];
		if (valid(nx, ny)) {
			if (map[nx][ny] == 2)
				return true;
		}
	}
	return false;
}
// 상대의 돌 그룹 검사
void go(int x, int y, int &cnt, bool flag) {
	check[x][y] = true;
	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d], ny = y + dy[d];
		if (valid(nx, ny)) {
			if (!map[nx][ny])
				cnt = 0, flag = true;
			else if (map[nx][ny] == 2 && !check[nx][ny]) {
				if (!flag)	cnt++;
				go(nx, ny, cnt, flag);
			}
		}
	}
}
// 상대의 죽은 돌 개수 검사
int count(void) {
	int ret = 0;
	// 전체 맵 검사
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < M; y++) {
			if (map[x][y] == 2 && !check[x][y]) { // 아직 검사하지 않은 상대의 돌
				int cnt = 1;
				go(x, y, cnt, false);	// 해당 위치에서 상대 돌 그룹 검사
				ret += cnt;
			}
		}
	}
	// 검사 체크 해제
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			check[i][j] = false;

	return ret;
}

int main(void) {
	// 입력부
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			scanf("%d", &map[i][j]);
	// 처리부
	for (int x1 = 0; x1 < N; x1++) {	// 첫 번째 돌을 놓을 위치 탐색
		for (int y1 = 0; y1 < M; y1++) {
			if (adjacent(x1, y1)) {	// 상대의 돌에 인접한 위치인 경우
				map[x1][y1] = 1;	// 해당 위치에 첫 번째 돌을 놓음
				for (int x2 = x1; x2 < N; x2++) {	// 두 번째 돌을 놓을 위치 탐색
					for (int y2 = (x1 == x2) ? y1 + 1 : 0; y2 < M; y2++) {
						if (adjacent(x2, y2)) {	// 상대의 돌에 인접한 위치인 경우
							map[x2][y2] = 1;	// 해당 위치에 두 번째 돌을 놓음
							ans = max(ans, count());	// 상대의 죽은 돌 개수 검사
							map[x2][y2] = 0;	// 두 번째 돌 회수
						}
					}
				}
				map[x1][y1] = 0;	// 첫 번째 돌 회수
			}
		}
	}
	// 출력부
	printf("%d\n", ans);
	return 0;
}