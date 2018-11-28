/*
https://www.acmicpc.net/problem/16235
*/

#include <cstdio>
#include <queue>
#define PRIORITY	1000
using namespace std;
typedef struct { int x, y, l; } point;

queue<point> q[PRIORITY];	// �켱���� ť
int map[10][10], A[10][10];
int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
int N, M, K;

void spring(void) {
	int qsize[PRIORITY];
	for (int p = 1; p < PRIORITY; p++)
		// ������ ���̸� �������Ѽ� �ٽ� ť�� �����ϹǷ� ť ����� ���÷� �޶���
		// ���� �̸� ���� ť ����� �����ؾ� ��
		qsize[p] = q[p].size();

	for (int p = 1; p < PRIORITY; p++) {
		while (qsize[p]--) {
			point pnt = q[p].front();
			q[p].pop();
			if (map[pnt.x][pnt.y] >= p) {	// ����� ����� ���
				map[pnt.x][pnt.y] -= p;		// ��� ����
				pnt.l++;					// ���� ����
				q[pnt.l].push(pnt);			// �ش� ������ ť�� ����
			}
			else				// ����� ������ ���
				q[0].push(pnt);	// ������ �׾� 0��° ť�� ����
		}
	}
}

void summer(void) {
	int qsize = q[0].size();
	while (qsize--) {
		point pnt = q[0].front();
		q[0].pop();
		map[pnt.x][pnt.y] += pnt.l / 2;	// ���� ���� ������ ������ ������� �߰�
	}
}

void fall(void) {
	// ���̰� 5�� ����� ������ ����
	for (int p = 5; p < PRIORITY; p += 5) {
		int qsize = q[p].size();
		while (qsize--) {
			point pnt = q[p].front();
			q[p].pop();
			for (int d = 0; d < 8; d++) {
				int nx = pnt.x + dx[d], ny = pnt.y + dy[d];
				if (0 <= nx && nx < N && 0 <= ny && ny < N)
					q[1].push({ nx, ny, 1 });	// ���� ������ ��ġ�� ���� 1�� ���� ����
			}
			q[p].push(pnt);	// ���ο� ������ ���Ľ�Ų ������ �ٽ� ť�� ����
		}
	}
}

void winter(void) {
	// ��� �߰�
	for (int x = 0; x < N; x++)
		for (int y = 0; y < N; y++)
			map[x][y] += A[x][y];
}

int main(void) {
	int ans = 0;
	scanf("%d %d %d", &N, &M, &K);
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			scanf("%d", &A[x][y]);
			map[x][y] = 5;
		}
	}
	for (int m = 0; m < M; m++) {
		int x, y, l;
		scanf("%d %d %d", &x, &y, &l);
		q[l].push({ x - 1, y - 1, l });
	}

	while (K--)
		spring(), summer(), fall(), winter();

	for (int p = 1; p < PRIORITY; p++)
		ans += q[p].size();
	printf("%d\n", ans);

	return 0;
}