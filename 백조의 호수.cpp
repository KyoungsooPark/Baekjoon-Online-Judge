/*
https://www.acmicpc.net/problem/3197
*/

#include <cstdio>
#include <queue>
using namespace std;
struct point { int x, y; };

queue<point> sq[2], wq[2];
point L2[2];
bool visited[1500][1500];
char map[1500][1500];
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int R, C, scur = 0, wcur = 0, ans = 0;
// �� bfs Ž��. ���ϸ� ������ ���� ���� �� �ش� ��ġ�� ���� next queue�� ����
void water(void) {
	int next = 1 - wcur;
	while (!wq[wcur].empty()) {
		point w = wq[wcur].front(); wq[wcur].pop();
		for (int d = 0; d < 4; d++) {
			int nx = w.x + dx[d], ny = w.y + dy[d];
			if (0 <= nx && nx < R && 0 <= ny && ny < C && map[nx][ny] == 'X') {
				wq[next].push({ nx, ny });
				map[nx][ny] = '.';
			}
		}
	}
	wcur = next;
}
// ���� bfs Ž��. ���ϸ� ������ �ش� ��ġ�� ������ next queue�� ����
bool swan(void) {
	int next = 1 - scur;
	while (!sq[scur].empty()) {
		point w = sq[scur].front(); sq[scur].pop();
		for (int d = 0; d < 4; d++) {
			int nx = w.x + dx[d], ny = w.y + dy[d];
			if (0 <= nx && nx < R && 0 <= ny && ny < C && !visited[nx][ny]) {
				if (nx == L2[1].x && ny == L2[1].y)
					return true;
				if (map[nx][ny] == '.')
					sq[scur].push({ nx, ny });
				else if (map[nx][ny] == 'X')
					sq[next].push({ nx, ny });
				visited[nx][ny] = true;
			}
		}
	}
	scur = next;
	return false;
}

int main(void) {
	int idx = 0;
	// �Էº�
	scanf("%d %d", &R, &C);
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			scanf(" %c", &map[i][j]);
			if (map[i][j] != 'X')
				wq[wcur].push({ i, j });
			if (map[i][j] == 'L') {
				if (idx == 0)
					sq[scur].push({ i, j });
				L2[idx++] = { i, j };
				map[i][j] = '.';
			}
		}
	}
	// ó����
	while (!swan()) { water(); ans++; }
	// ��º�
	printf("%d\n", ans);
	return 0;
}