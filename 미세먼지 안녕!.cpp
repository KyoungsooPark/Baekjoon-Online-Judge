/*
https://www.acmicpc.net/problem/17144
*/

#include <cstdio>
#include <vector>
using namespace std;
struct point { int x, y; };

vector<point> v;
int A[50][50], cpy[50][50];
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int R, C, T;
// �� �̼������� ���
int total(void) {
	int ret = 0;
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			if (A[i][j] > 0)
				ret += A[i][j];
	return ret;
}
// �̼����� Ȯ��
void defuse(void) {
	// �ϰ� ������ ���� �� ī��
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			cpy[i][j] = A[i][j];
	// �̼����� Ȯ��
	for (int x = 0; x < R; x++)
		for (int y = 0; y < C; y++)
			if (int sub = A[x][y] / 5) {	// �̼����� Ȯ���� ������ ���
				for (int d = 0; d < 4; d++) {
					int nx = x + dx[d], ny = y + dy[d];
					if (0 <= nx && nx < R && 0 <= ny && ny < C && A[nx][ny] != -1)
						cpy[nx][ny] += sub, cpy[x][y] -= sub;
				}
			}
	// ī�Ǹ��� �̿��� �ϰ� ������Ʈ
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			A[i][j] = cpy[i][j], cpy[i][j] = 0;
}
// ���� û��
void clean(void) {
	int x = v[0].x - 1, y = v[0].y;
	// ���� ����û������ �ݽð���� ��ȯ
	while (x) { A[x][y] = A[x - 1][y], x--; }
	while (y < C - 1) { A[x][y] = A[x][y + 1], y++; }
	while (x < v[0].x) { A[x][y] = A[x + 1][y], x++; }
	while (y > 1) { A[x][y] = A[x][y - 1], y--; }
	A[x][y] = 0;	// ����û���⿡ ������ ����
	// �Ʒ��� ����û������ �ð���� ��ȯ
	x = v[1].x + 1, y = v[1].y;
	while (x < R - 1) { A[x][y] = A[x + 1][y], x++; }
	while (y < C - 1) { A[x][y] = A[x][y + 1], y++; }
	while (x > v[1].x) { A[x][y] = A[x - 1][y], x--; }
	while (y > 1) { A[x][y] = A[x][y - 1], y--; }
	A[x][y] = 0;	// ����û���⿡ ������ ����
}

int main(void) {
	// �Էº�
	scanf("%d %d %d", &R, &C, &T);
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++) {
			scanf("%d", &A[i][j]);
			if (A[i][j] == -1)	v.push_back({ i, j });
		}
	// ó����
	while (T--) {
		defuse();
		clean();
	}
	// ��º�
	printf("%d\n", total());
	return 0;
}