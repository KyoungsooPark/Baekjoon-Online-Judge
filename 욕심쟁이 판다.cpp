/*
https://www.acmicpc.net/problem/1937
*/

#include <cstdio>
using namespace std;
int map[500][500];	// �볪�� �� ����
int check[500][500];	// check[x][y]: ��ǥ (x, y)���� �湮�� �� �ִ� �ִ� ����
int dx[4] = { 0, 0, 1, -1 };	// ��, ��, ��, ��
int dy[4] = { 1, -1, 0, 0 };	// ��, ��, ��, ��
int N, ans = 0;

int max(int a, int b) { return a >= b ? a : b; }
// �ֺ��� Ž���ϸ� ��ǥ (x, y)���� �湮�� �� �ִ� �ִ� ���� ������Ʈ �� ��ȯ
int go(int x, int y) {
	if (check[x][y])	// �̹� �˻��Ͽ� check[x][y]�� ������ �����ϴ� ���
		return check[x][y];	// �ش� ���� ��ȯ

	bool flag = false;	// �ֺ��� �湮 ���� ���� ������ �˻��ϱ� ���� flag
	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d], ny = y + dy[d];
		if (0 <= nx && nx < N && 0 <= ny && ny < N) {
			if (map[nx][ny] > map[x][y]) {	// �湮 ���� ������ ���
				flag = true;	// flag set
				// ���� ������ �ش� ���� Ž�� ���� �� �� ������Ʈ
				check[x][y] = max(check[x][y], go(nx, ny) + 1);
			}
		}
	}
	if (!flag)	// �湮 ���� ������ �������� �ʴ� ���
		return check[x][y] = 1;	// ���� ������ ���̸� 1�� ���� �� ��ȯ
	return check[x][y];	// Ž�� ��� ��ȯ
}

int main(void) {
	// �Էº�
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &map[i][j]);
	// ó����
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (!check[i][j])
				ans = max(ans, go(i, j));
	// ��º�
	printf("%d\n", ans);
	return 0;
}