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

// ����� ���� ������ ��ġ���� �˻�
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
// ����� �� �׷� �˻�
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
// ����� ���� �� ���� �˻�
int count(void) {
	int ret = 0;
	// ��ü �� �˻�
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < M; y++) {
			if (map[x][y] == 2 && !check[x][y]) { // ���� �˻����� ���� ����� ��
				int cnt = 1;
				go(x, y, cnt, false);	// �ش� ��ġ���� ��� �� �׷� �˻�
				ret += cnt;
			}
		}
	}
	// �˻� üũ ����
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			check[i][j] = false;

	return ret;
}

int main(void) {
	// �Էº�
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			scanf("%d", &map[i][j]);
	// ó����
	for (int x1 = 0; x1 < N; x1++) {	// ù ��° ���� ���� ��ġ Ž��
		for (int y1 = 0; y1 < M; y1++) {
			if (adjacent(x1, y1)) {	// ����� ���� ������ ��ġ�� ���
				map[x1][y1] = 1;	// �ش� ��ġ�� ù ��° ���� ����
				for (int x2 = x1; x2 < N; x2++) {	// �� ��° ���� ���� ��ġ Ž��
					for (int y2 = (x1 == x2) ? y1 + 1 : 0; y2 < M; y2++) {
						if (adjacent(x2, y2)) {	// ����� ���� ������ ��ġ�� ���
							map[x2][y2] = 1;	// �ش� ��ġ�� �� ��° ���� ����
							ans = max(ans, count());	// ����� ���� �� ���� �˻�
							map[x2][y2] = 0;	// �� ��° �� ȸ��
						}
					}
				}
				map[x1][y1] = 0;	// ù ��° �� ȸ��
			}
		}
	}
	// ��º�
	printf("%d\n", ans);
	return 0;
}