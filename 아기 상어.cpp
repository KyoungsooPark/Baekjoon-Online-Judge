/*
https://www.acmicpc.net/problem/16236
*/

#include <cstdio>
#include <queue>
using namespace std;
typedef struct { int x, y, z; } point;
typedef struct { int x, y, size, cnt; } shark;

shark s;
int map[20][20];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int N, ans;

// ������(dstx, dsty)������ �̵��Ÿ� ��ȯ
// limit�� �ʰ��ϰų� ������ �� ������ 2e9 ��ȯ
int distance(int dstx, int dsty, int limit) {
	queue<point> q;
	bool visited[20][20] = { false, };

	visited[s.x][s.y] = true, q.push({ s.x, s.y, 0 });
	while (!q.empty()) {
		point p = q.front();
		q.pop();
		if (p.x == dstx && p.y == dsty)	// �������� ������ ���
			return p.z;	// �̵��Ÿ� ��ȯ
		if (p.z >= limit)	// limit�� �ʰ��ϴ� ���
			return 2e9;

		for (int d = 0; d < 4; d++) {
			int nx = p.x + dx[d], ny = p.y + dy[d];
			if (0 <= nx && nx < N && 0 <= ny && ny < N && visited[nx][ny] == false)
				if (map[nx][ny] <= s.size)
					visited[nx][ny] = true, q.push({ nx, ny, p.z + 1 });
		}
	}
	return 2e9;	// �������� ������ �� ���� ���
}

bool move(void) {
	int nx, ny, dist = 2e9;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (0 < map[i][j] && map[i][j] < s.size) {	// ���� ������ Ž��
				int temp = distance(i, j, dist);	// ������������ �̵��Ÿ�
				if (dist > temp) {	// �̵��Ÿ��� ���� ����� ������ ����
					dist = temp;
					nx = i, ny = j;
				}
			}
		}
	}
	if (dist == 2e9)	// ������ �������� ���� ���
		return false;	// false ��ȯ

	s.x = nx, s.y = ny;	// �������� �̵�
	map[nx][ny] = 0;	// �ش� ��ġ�� ����⸦ ����
	ans += dist;	// �� �̵��Ÿ� ����
	if (--s.cnt == 0) {	// �Ʊ� �� �ڽ��� ũ�⸸ŭ�� ����⸦ ���� ���
		s.size++;	// ũ�� ����
		s.cnt = s.size;	// ���� ũ�� �������� �Ծ�� �� ����� �� ����
	}
	return true;
}



int main(void) {
	// �Էº�
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 9) {
				map[i][j] = 0;
				s = { i, j, 2, 2 };
			}
		}
	}

	// ó����
	while (move());

	// ��º�
	printf("%d\n", ans);

	return 0;
}