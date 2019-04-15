/*
https://www.acmicpc.net/problem/17143
*/

#include <cstdio>
#include <vector>
#define DEAD	-1
using namespace std;
struct shark { int x, y, s, d, z; };

shark S[10001];
int map[100][100], cpy[100][100];
int dx[5] = { 0, -1, 1, 0, 0 };
int dy[5] = { 0, 0, 0, 1, -1 };
int R, C, M, max_size = 0, min_size = 2e9, ans = 0;

int max(int a, int b) { return a > b ? a: b; }
int min(int a, int b) { return a < b ? a : b; }

void jaksal(int c) {
	for (int r = 0; r < R; r++) {
		if (map[r][c]) {
			S[map[r][c]].z = DEAD;
			ans += map[r][c];
			map[r][c] = 0;
			break;
		}
	}
}
// ��� �̵�
void move(shark &s) {
	int n = s.s, nx, ny;
	while (n--) {	// ��� �ӵ���ŭ �̵�
		nx = s.x + dx[s.d], ny = s.y + dy[s.d];
		if (0 <= nx && nx < R && 0 <= ny && ny < C) {
			s.x = nx, s.y = ny;
			continue;
		}
		switch (s.d) {	// �� ���� ������ ���̻� ���� �Ұ� �� ���� ��ȯ
		case 1: case 3: s.d++; break;
		case 2: case 4: s.d--; break;
		}
		s.x += dx[s.d], s.y += dy[s.d];	// �ٲ� �������� �̵�
	}
}
// ��� ��� �̵�
void mulgogi(void) {
	for (int i = min_size; i <= max_size; i++) {
		if (S[i].z != DEAD) {	// ���� ��� ����
			if (map[S[i].x][S[i].y] != S[i].z) {	// ��Ƹ��� ���
				S[i].z = DEAD;	// ���� ��� ǥ��
				continue;
			}
			move(S[i]);	// ���� ���� ��� �̵�
			cpy[S[i].x][S[i].y] = max(cpy[S[i].x][S[i].y], S[i].z);	// ũ�Ⱑ ���� ū �� �ش� ��ġ ����
		}
	}
	// �� ������Ʈ
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			map[i][j] = cpy[i][j], cpy[i][j] = 0;
}

int main(void) {
	scanf("%d %d %d", &R, &C, &M);
	while (M--) {
		int r, c, s, d, z;
		scanf("%d %d %d %d %d", &r, &c, &s, &d, &z);
		S[z] = { --r, --c, s, d, z };
		map[r][c] = z;
		max_size = max(max_size, z);
		min_size = min(min_size, z);
	}
	for (int c = 0; c < C; c++) {
		jaksal(c);
		mulgogi();
	}
	printf("%d\n", ans);
	return 0;
}