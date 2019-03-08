/*
https://www.acmicpc.net/problem/1937
*/

#include <cstdio>
using namespace std;

int map[500][500];	// �볪�� �� ����
int check[500][500];	// check[x][y]: ��ǥ (x, y)���� �湮 ������ �ִ� ����
int dx[4] = { 0, 0, 1, -1 };	// ��, ��, ��, ��
int dy[4] = { 1, -1, 0, 0 };	// ��, ��, ��, ��
int n, ans = 0;

int max(int a, int b) { return a >= b ? a : b; }
// �ֺ��� Ž���ϸ� ��ǥ (x, y)���� �湮 ������ �ִ� ���� ������Ʈ
void go(int x, int y) {
	bool flag = false;	// �ֺ��� �湮 ���� ���� ������ �˻��ϱ� ���� flag
	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d], ny = y + dy[d];
		if (0 <= nx && nx < n && 0 <= ny && ny < n) {	// Ž�� ���� �̳�
			if (map[x][y] < map[nx][ny]) {	// �湮 ���� ����
				if (!check[nx][ny])	// �ش� �湮 ���� ������ ���� Ž������ ���� ���
					go(nx, ny);	// Ž��
				check[x][y] = max(check[x][y], check[nx][ny] + 1); // ���� ������ Ž�� ��� �� �� ������Ʈ
				flag = true;	// flag set
			}
		}
	}
	if (!flag)	// �湮 ���� ������ �������� �ʴ� ���
		check[x][y] = 1;	// ���� ������ ���̸� 1�� ���� �� ��ȯ
	ans = max(ans, check[x][y]);
}

int main(void) {
	// �Էº�
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &map[i][j]);
	// ó����
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (!check[i][j])
				go(i, j);
	// ��º�
	printf("%d\n", ans);
	return 0;
}