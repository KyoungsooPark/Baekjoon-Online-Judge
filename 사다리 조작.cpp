/*
https://www.acmicpc.net/problem/15684
*/

#include <cstdio>
using namespace std;

bool map[31][11];
int N, H, M, num, ans = -1;

// ���μ��� ��ȿ�� �˻�
bool check(void) {
	for (int n = 1; n <= N; n++) {
		int nn = n;
		for (int h = 1; h <= H; h++) {
			if (map[h][nn])	// ���μ� �����ʿ� ���μ� ����
				nn++;
			else if (nn > 1 && map[h][nn - 1])	// ���μ� ���ʿ� ���μ� ����
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
			// ���μ��� ���ӵ� ���
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
	// �Էº�
	scanf("%d %d %d", &N, &M, &H);
	while (M--) {
		int x, y;
		scanf("%d %d", &x, &y);
		map[x][y] = true;
	}
	// ó����
	for (num = 0; num < 4; num++) {
		go(1, num);
		if (ans != -1) break;
	}
	// ��º�
	printf("%d\n", ans);
	return 0;
}