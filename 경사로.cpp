/*
https://www.acmicpc.net/problem/14890
*/

#include <cstdio>
using namespace std;

int map[100][100];
int N, L, ans = 0;

void row(int x, int y, bool flag) {
	if (y == N - 1) {	// 길의 끝에 도달
		ans++;
		return;
	}
	if (y + L < N && map[x][y + L] == map[x][y] + 1) {	// 오르막
		if (flag) return;	// 해당 위치에 내리막 경사로를 설치한 경우
		for (int i = y + 1; i < y + L; i++)
			if (map[x][i] != map[x][y])	// 길이 평탄하지 않아서 경사로 설치 불가
				return;
		row(x, y + L, false);	// 경사로 설치 후 다음 위치로 이동
	}
	else if (y + 1 < N && map[x][y] == map[x][y + 1])	// 평지
		row(x, y + 1, false);
	else if (y + L < N && map[x][y + L] == map[x][y] - 1) {	// 내리막
		for (int i = y + 1; i < y + L; i++)
			if (map[x][i] != map[x][y + L])	// 길이 평탄하지 않아서 경사로 설치 불가
				return;
		row(x, y + L, true);	// 경사로 설치 후 다음 위치로 이동
	}
}

void col(int x, int y, bool flag) {
	if (x == N - 1) {	// 길의 끝에 도달
		ans++;
		return;
	}
	if (x + L < N && map[x + L][y] == map[x][y] + 1) {	// 오르막
		if (flag) return;	// 해당 위치에 내리막 경사로를 설치한 경우
		for (int i = x + 1; i < x + L; i++)
			if (map[i][y] != map[x][y])	// 길이 평탄하지 않아서 경사로 설치 불가
				return;
		col(x + L, y, false);	// 경사로 설치 후 다음 위치로 이동
	}
	else if (x + 1 < N && map[x][y] == map[x + 1][y])	// 평지
		col(x + 1, y, false);
	else if (x + L < N && map[x + L][y] == map[x][y] - 1) {	// 내리막
		for (int i = x + 1; i < x + L; i++)
			if (map[i][y] != map[x + L][y])	// 길이 평탄하지 않아서 경사로 설치 불가
				return;
		col(x + L, y, true);	// 경사로 설치 후 다음 위치로 이동
	}
}

int main(void) {
	// 입력부
	scanf("%d %d", &N, &L);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &map[i][j]);

	// 처리부
	for (int i = 0; i < N; i++) {
		row(i, 0, false);
		col(0, i, false);
	}

	// 출력부
	printf("%d\n", ans);
	return 0;
}