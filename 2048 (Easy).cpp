/*
https://www.acmicpc.net/problem/12100
*/

#include <cstdio>
#define NOT_MERGED	0
#define MERGED		1
using namespace std;

int board[20][20], dir[5];
int N, ans;

void move(int &src, int &dst) {
	dst = src;
	src = 0;
}

void merge(int &src, int &dst, int &flag) {
	if (src == dst && flag == NOT_MERGED) {
		dst *= 2;
		flag = MERGED;
		src = 0;
	}
}

void go(int n) {
	if (n == 5) {
		int cpy[20][20][2];
		for (int r = 0; r < N; r++)
			for (int c = 0; c < N; c++) {
				cpy[r][c][0] = board[r][c];
				cpy[r][c][1] = NOT_MERGED;
			}

		for (int i = 0; i < n; i++) {
			switch (dir[i]) {
			case 0:	// 상
				for (int r = 1; r < N; r++) {
					for (int c = 0; c < N; c++) {
						if (cpy[r][c][0] != 0) {	// 움직일 블록이 존재하는 경우
							for (int j = r; j > 0; j--) {	// 움직일 위치의 블록 탐색
								if (cpy[j - 1][c][0] == 0)
									// 블록이 없으면 move
									move(cpy[j][c][0], cpy[j - 1][c][0]);
								else {
									// 움직일 위치에 블록이 존재하는 경우 merge
									merge(cpy[j][c][0], cpy[j - 1][c][0], cpy[j - 1][c][1]);
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
								if (cpy[j + 1][c][0] == 0)
									move(cpy[j][c][0], cpy[j + 1][c][0]);
								else {
									merge(cpy[j][c][0], cpy[j + 1][c][0], cpy[j + 1][c][1]);
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
								if (cpy[r][j - 1][0] == 0)
									move(cpy[r][j][0], cpy[r][j - 1][0]);
								else {
									merge(cpy[r][j][0], cpy[r][j - 1][0], cpy[r][j - 1][1]);
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
								if (cpy[r][j + 1][0] == 0)
									move(cpy[r][j][0], cpy[r][j + 1][0]);
								else {
									merge(cpy[r][j][0], cpy[r][j + 1][0], cpy[r][j + 1][1]);
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
