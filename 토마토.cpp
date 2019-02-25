/*
https://www.acmicpc.net/problem/7576
*/

#include <cstdio>
#include <queue>
using namespace std;
typedef struct { int x, y; } point;

int map[1000][1000];
int dx[4] = { 0, 0, 1, -1 };	// ��, ��, ��, ��
int dy[4] = { 1, -1, 0, 0 };	// ��, ��, ��, ��

int main(void) {
	int N, M, ans = -1;
	queue<point> q;
	// �Էº�
	scanf("%d %d", &M, &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 1)
				q.push({ i, j });
		}
	}
	// ó����
	while (!q.empty()) {
		int size = q.size();
		while (size--) {	// ����(generation) ���� ����
			point now = q.front();
			q.pop();
			for (int d = 0; d < 4; d++) {
				int nx = now.x + dx[d], ny = now.y + dy[d];
				if (0 <= nx && nx < N && 0 <= ny && ny < M) {	// â�� ������ ����� ���� ��
					if (!map[nx][ny]) {	// ���� ���� �丶�䰡 ������ ���
						map[nx][ny] = 1;	// �ش� �丶�� ����
						q.push({ nx, ny });	// ���� �丶�� ��ġ ť�� ����
					}
				}
			}
		}
		ans++;
	}
	// ��º�
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (!map[i][j]) {	// ���� ���� �丶�䰡 �ִ� ���
				ans = -1;
				break;
			}
		}
		if (ans == -1)
			break;
	}
	printf("%d\n", ans);
	return 0;
}