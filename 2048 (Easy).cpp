/*
https://www.acmicpc.net/problem/12100
*/

#include <cstdio>
#define MERGED		true
#define NOT_MERGED	false
using namespace std;

int board[20][20], dir[5];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int N, ans;

void go(int n) {
	if (n == 5) {
		int cpy[20][20][2];
		for (int r = 0; r < N; r++)
			for (int c = 0; c < N; c++) {
				cpy[r][c][0] = board[r][c];
				cpy[r][c][1] = false;
			}

		for (int i = 0; i < n; i++) {
			switch (dir[i]) {
			case 0:	// 상
				for (int r = 1; r < N; r++) {
					for (int c = 0; c < N; c++) {
						if (cpy[r][c][0] != 0) {	// 움직일 블록이 존재하는 경우
							for (int j = r; j > 0; j--) {	// 움직일 위치의 블록 탐색
								if (cpy[j - 1][c][0] == 0) {	// 블록이 없으면
									cpy[j - 1][c][0] = cpy[j][c][0];	// 블록을 한 칸 이동
									cpy[j][c][0] = 0;
								}
								else {	// 움직일 위치에 블록이 존재하는 경우
									// 움직일 블록과 함칠 수 있는지 검사
									if (cpy[j - 1][c][0] == cpy[j][c][0] && cpy[j - 1][c][1] == NOT_MERGED) {
										cpy[j - 1][c][0] += cpy[j][c][0];
										cpy[j - 1][c][1] = MERGED;
										cpy[j][c][0] = 0;
									}
									break;
								}
							}
						}
					}
				}
				break;
			case 1:	// 하
				for (int r = N - 2; r >= 0; r--) {
					for (int c = 0; c < N; c++) {
						if (cpy[r][c][0] != 0) {
							for (int j = r; j < N - 1; j++) {
								if (cpy[j + 1][c][0] == 0) {
									cpy[j + 1][c][0] = cpy[j][c][0];
									cpy[j][c][0] = 0;
								}
								else {
									if (cpy[j + 1][c][0] == cpy[j][c][0] && cpy[j + 1][c][1] == NOT_MERGED) {
										cpy[j + 1][c][0] += cpy[j][c][0];
										cpy[j + 1][c][1] = MERGED;
										cpy[j][c][0] = 0;
									}
									break;
								}
							}
						}
					}
				}
				break;
			case 2:	// 좌
				for (int r = 0; r < N; r++) {
					for (int c = 1; c < N; c++) {
						if (cpy[r][c][0] != 0) {
							for (int j = c; j > 0; j--) {
								if (cpy[r][j - 1][0] == 0) {
									cpy[r][j - 1][0] = cpy[r][j][0];
									cpy[r][j][0] = 0;
								}
								else {
									if (cpy[r][j - 1][0] == cpy[r][j][0] && cpy[r][j - 1][1] == NOT_MERGED) {
										cpy[r][j - 1][0] += cpy[r][j][0];
										cpy[r][j - 1][1] = MERGED;
										cpy[r][j][0] = 0;
									}
									break;
								}
							}
						}
					}
				}
				break;
			case 3:	// 우
				for (int r = 0; r < N; r++) {
					for (int c = N - 2; c >= 0; c--) {
						if (cpy[r][c][0] != 0) {
							for (int j = c; j < N - 1; j++) {
								if (cpy[r][j + 1][0] == 0) {
									cpy[r][j + 1][0] = cpy[r][j][0];
									cpy[r][j][0] = 0;
								}
								else {
									if (cpy[r][j + 1][0] == cpy[r][j][0] && cpy[r][j + 1][1] == NOT_MERGED) {
										cpy[r][j + 1][0] += cpy[r][j][0];
										cpy[r][j + 1][1] = MERGED;
										cpy[r][j][0] = 0;
									}
									break;
								}
							}
						}
					}
				}
				break;
			}
			// 모든 블록을 이동 방향으로 움직인 후 flag 초기화
			for (int r = 0; r < N; r++)
				for (int c = 0; c < N; c++)
					cpy[r][c][1] = NOT_MERGED;
		}
		// 최대값 탐색
		for (int r = 0; r < N; r++)
			for (int c = 0; c < N; c++)
				if (ans < cpy[r][c][0])
					ans = cpy[r][c][0];
		return;
	}

	for (int i = 0; i < 4; i++) {
		dir[n] = i;
		go(n + 1);
	}
}

int main(void) {
	scanf("%d", &N);
	for (int r = 0; r < N; r++)
		for (int c = 0; c < N; c++)
			scanf("%d", &board[r][c]);

	go(0);
	printf("%d\n", ans);
	return 0;
}
