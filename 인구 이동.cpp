/*
https://www.acmicpc.net/problem/16234
*/

#include <cstdio>
#include <queue>
#include <vector>
using namespace std;
typedef struct { int x, y; } point;

vector<point> v;
bool flag;	// �α� �̵� ����
bool check[50][50];
int map[50][50];
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int N, L, R, ans = 0;

int abs(int num) { return num >= 0 ? num : -num; }

void go(int x, int y, int &sum, int &n) {
	check[x][y] = true;		// �湮 üũ
	sum += map[x][y], n++;	// ������ �α� ��, ���� �� ������Ʈ
	v.push_back({ x, y });	// ������ ������ ��ġ ����

	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d], ny = y + dy[d];
		if (0 <= nx && nx < N && 0 <= ny && ny < N && !check[nx][ny]) {
			int temp = abs(map[x][y] - map[nx][ny]);	// �α� ���� ���
			if (L <= temp && temp <= R) {				// �α� �̵� ����
				flag = true;
				go(nx, ny, sum, n);
			}
		}
	}
}

int main(void) {
	// �Էº�
	scanf("%d %d %d", &N, &L, &R);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &map[i][j]);
	// ó����
	do {
		flag = false;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (!check[i][j]) {
					int sum = 0,	// ������ �α� ��
						n = 0,		// ������ ���� ��
						mean;		// ���
					go(i, j, sum, n);	// �̵� ���� ���� ����
					mean = sum / n;
					// ������ ������ �α� �̵�
					for (point p : v)
						map[p.x][p.y] = mean;
					v.clear();
				}
			}
		}

		if (flag) {	// �α� �̵��� ��� Ƚ�� ���� �� check �ʱ�ȭ
			ans++;
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					check[i][j] = false;
		}
	} while (flag);
	// ��º�
	printf("%d\n", ans);
	return 0;
}