/*
https://www.acmicpc.net/problem/17142
*/

#include <cstdio>
#include <vector>
#include <queue>
#define INF	0x1FFFFFFF
using namespace std;
struct point { int x, y; };

vector<point> v;
int map[50][50], cpy[50][50];
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int N, M, empty_space = 0, ans = INF;

int min(int a, int b) { return a < b ? a : b; }

int simulation(int selected) {
	queue<point> q;
	int ret = 0, remain = empty_space;
	bool empty_space = false;
	// �ùķ��̼��� ���� �� ī��
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cpy[i][j] = map[i][j];

	// ���õ� ���̷����� ť�� ����
	for (int i = 0; i < v.size(); i++) {
		if (selected & (1 << i)) {
			q.push(v[i]);
			cpy[v[i].x][v[i].y] = 1;
		}
	}
	// ���̷��� Ȯ��
	while (!q.empty()) {
		int size = q.size();
		ret++;
		while (size--) {
			point p = q.front(); q.pop();
			for (int d = 0; d < 4; d++) {
				int nx = p.x + dx[d], ny = p.y + dy[d];
				// ���� ��ġ�� ���� �ƴϰ� �湮���� ���� ���� ���
				if (0 <= nx && nx < N && 0 <= ny && ny < N && cpy[nx][ny] != 1) {
					if (!cpy[nx][ny] && !--remain)	// ������ �� ĭ�� ���
						return ret;	// �ش� ĭ �ڿ� ��Ȱ�� ���̷����� �ִ��� ����
					q.push({ nx, ny });
					cpy[nx][ny] = 1;
				}
			}
		}
	}
	return remain ? INF : ret;	// �� ĭ�� ���� ��� INF, ��� ä�� ��� �ɸ� �ð� ��ȯ
}

int main(void) {
	// �Էº�
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
			switch (map[i][j]) {
			case 0: empty_space++; break;
			case 2: v.push_back({ i, j });
			}
		}
	// ó����
	if (!empty_space) {	// �� ĭ�� ������ 0 ��� �� ����
		printf("0\n");
		return 0;
	}
	for (int i = 0; i < (1 << v.size()); i++) {
		int cnt = 0;
		for (int j = 0; j < v.size(); j++)
			if (i & (1 << j))
				cnt++;
		if (cnt == M)
			ans = min(ans, simulation(i));
	}
	// ��º�
	printf("%d\n", ans == INF ? -1 : ans);
	return 0;
}