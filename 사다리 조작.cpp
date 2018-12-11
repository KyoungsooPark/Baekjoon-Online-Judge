/*
https://www.acmicpc.net/problem/15684
*/

#include <cstdio>
using namespace std;

bool map[31][11];
int N, H, M, num, ans = -1;

// 가로선의 유효성 검사
bool check(void) {
	for (int n = 1; n <= N; n++) {
		int nn = n;
		for (int h = 1; h <= H; h++) {
			if (map[h][nn])	// 세로선 오른쪽에 가로선 존재
				nn++;
			else if (nn > 1 && map[h][nn - 1])	// 세로선 왼쪽에 가로선 존재
				nn--;
		}
		if (nn != n)
			return false;
	}
	return true;
}

void go(int row, int cnt) {
	if (cnt == 0) {
		if (check())
			ans = num;
		return;
	}

	for (int r = row; r <= H; r++) {
		for (int c = 1; c < N; c++) {
			// 가로선이 연속될 경우
			if (map[r][c] || map[r][c - 1] || map[r][c + 1])
				continue;
			map[r][c] = true;
			go(r, cnt - 1);
			map[r][c] = false;
			if (ans != -1)
				return;
		}
	}
}

int main(void) {
	// 입력부
	scanf("%d %d %d", &N, &M, &H);
	while (M--) {
		int x, y;
		scanf("%d %d", &x, &y);
		map[x][y] = true;
	}
	// 처리부
	for (num = 0; num < 4; num++) {
		go(1, num);
		if (ans != -1) break;
	}
	// 출력부
	printf("%d\n", ans);
	return 0;
}