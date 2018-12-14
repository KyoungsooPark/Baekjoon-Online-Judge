/*
https://www.acmicpc.net/problem/14890
*/

#include <cstdio>
using namespace std;

int map[100][100];
int N, L, ans = 0;

void row(int x, int y, bool flag) {
	if (y == N - 1) {	// ���� ���� ����
		ans++;
		return;
	}
	if (y + L < N && map[x][y + L] == map[x][y] + 1) {	// ������
		if (flag) return;	// �ش� ��ġ�� ������ ���θ� ��ġ�� ���
		for (int i = y + 1; i < y + L; i++)
			if (map[x][i] != map[x][y])	// ���� ��ź���� �ʾƼ� ���� ��ġ �Ұ�
				return;
		row(x, y + L, false);	// ���� ��ġ �� ���� ��ġ�� �̵�
	}
	else if (y + 1 < N && map[x][y] == map[x][y + 1])	// ����
		row(x, y + 1, false);
	else if (y + L < N && map[x][y + L] == map[x][y] - 1) {	// ������
		for (int i = y + 1; i < y + L; i++)
			if (map[x][i] != map[x][y + L])	// ���� ��ź���� �ʾƼ� ���� ��ġ �Ұ�
				return;
		row(x, y + L, true);	// ���� ��ġ �� ���� ��ġ�� �̵�
	}
}

void col(int x, int y, bool flag) {
	if (x == N - 1) {	// ���� ���� ����
		ans++;
		return;
	}
	if (x + L < N && map[x + L][y] == map[x][y] + 1) {	// ������
		if (flag) return;	// �ش� ��ġ�� ������ ���θ� ��ġ�� ���
		for (int i = x + 1; i < x + L; i++)
			if (map[i][y] != map[x][y])	// ���� ��ź���� �ʾƼ� ���� ��ġ �Ұ�
				return;
		col(x + L, y, false);	// ���� ��ġ �� ���� ��ġ�� �̵�
	}
	else if (x + 1 < N && map[x][y] == map[x + 1][y])	// ����
		col(x + 1, y, false);
	else if (x + L < N && map[x + L][y] == map[x][y] - 1) {	// ������
		for (int i = x + 1; i < x + L; i++)
			if (map[i][y] != map[x + L][y])	// ���� ��ź���� �ʾƼ� ���� ��ġ �Ұ�
				return;
		col(x + L, y, true);	// ���� ��ġ �� ���� ��ġ�� �̵�
	}
}

int main(void) {
	// �Էº�
	scanf("%d %d", &N, &L);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &map[i][j]);

	// ó����
	for (int i = 0; i < N; i++) {
		row(i, 0, false);
		col(0, i, false);
	}

	// ��º�
	printf("%d\n", ans);
	return 0;
}