/*
https://www.acmicpc.net/problem/16236
*/

#include <cstdio>
#include <queue>
using namespace std;
typedef struct { int x, y, dist; } point;
typedef struct { int x, y, size, cnt; } shark;

shark baby_shark;
int map[20][20];
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int N, ans = 0;

// ���� �� �ִ� ����� ���� ���� ��ȯ
bool eatable(int x, int y) { return 0 < map[x][x] && map[x][x] < baby_shark.size; }
// �̵� ���� ���� ��ȯ
bool passable(int x, int y) { return map[x][x] == 0 || map[x][x] == baby_shark.size; }

// bfs�� �̿��� ����� Ž��
point search(void) {
	int dist[20][20] = { 0 };	// "���� �� �ִ�" ������� �Ÿ� ����. 0���� �ʱ�ȭ
	point ret = { -1, -1, 400 };	// Ž�� ��� ��ȯ�� ���� ����
	queue<point> q;
	q.push({ baby_shark.x, baby_shark.y, 0 });	// ����� ���� ��ġ, �Ÿ� ���� push
	dist[baby_shark.x][baby_shark.y] = -1;	// ���� ��ġ Ž�� ǥ��
	
	while (!q.empty()) {	// ���� ��� ��ġ�κ��� ��ü �� Ž��
		point now = q.front(); q.pop();
		int ndist = now.dist + 1;	// ���� �̵��� ��ġ�� �Ÿ�
		for (int d = 0; d < 4; d++) {
			int nx = now.x + dx[d], ny = now.y + dy[d];
			if (0 <= nx && nx < N && 0 <= ny && ny < N && !dist[nx][ny]) {	// Ž������ ���� ��ġ
				// dist �迭 ������Ʈ
				if (eatable(nx, ny))	// ���� �� �ִ� ����� ����
					dist[nx][ny] = ndist;	// �Ÿ� ����
				else	// �� ���� �Ǵ� ���� �� ���� ����Ⱑ ����
					dist[nx][ny] = -1;	// Ž�� ǥ��
				// �̵� ���� ��ġ�� �̵�
				if (passable(nx, ny))	// �̵� ���� ��ġ
					q.push({ nx, ny, ndist });	// ť�� ����
			}
		}
	}
	// ���� ������ �Ÿ��� ���� ª�� ����� Ž��
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (0 < dist[i][j] && dist[i][j] < ret.dist)
					ret = { i, j, dist[i][j] };
	return ret;
}

bool move(void) {
	point p = search();	// ���� ����� ��ġ Ž��
	if (p.x == -1)	return false;	// ���̻� ���� �� �ִ� ����Ⱑ �������� �ʴ� ��� false ��ȯ
	map[baby_shark.x][baby_shark.y] = 0, map[p.x][p.y] = 9, ans += p.dist;
	baby_shark.x = p.x, baby_shark.y = p.y, baby_shark.cnt++;	// ��� ��ġ, ���� ����� �� ������Ʈ
	if (baby_shark.cnt == baby_shark.size)	// ���� ����� ���� ��� ũ��� �����ϸ�
		baby_shark.size++, baby_shark.cnt = 0;	// ũ�� ����, ���� ����� �� �ʱ�ȭ
	return true;
}

int main(void) {
	// �Էº�
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 9)	// ���
				baby_shark = { i, j, 2, 0 };	// ��� �ʱ�ȭ
		}
	}
	// ó����
	while (move());
	// ��º�
	printf("%d\n", ans);
	return 0;
}