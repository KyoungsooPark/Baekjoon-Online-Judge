/*
https://www.acmicpc.net/problem/2573
*/

#include <cstdio>
#include <queue>
using namespace std;
typedef struct { int x, y; } point;

queue<point> q;
bool check[300][300];
int map[2][300][300];
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int N, M, cur = 0, ans = 0;
// ���� ���� �˻縦 ���� dfs
void go(int x, int y) {
	check[x][y] = true;
	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d], ny = y + dy[d];
		if (map[cur][nx][ny] && !check[nx][ny]) // �湮���� ���� ����
			go(nx, ny);
	}
}
// ������ ���� ���� ��ȯ
int cluster(void) {
	int ret = 0;
	for (int i = 1; i < N - 1; i++)
		for (int j = 1; j < M - 1; j++)
			if (map[cur][i][j] && !check[i][j]) {
				go(i, j);
				ret++;
			}
	// check �迭 �ʱ�ȭ
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			check[i][j] = false;
	return ret;
}
// ������ �ٴٿ� ���� ���� ��ȯ
int count(point p) {
	int ret = 0;
	for (int d = 0; d < 4; d++) {
		int nx = p.x + dx[d], ny = p.y + dy[d];
		if (!map[cur][nx][ny])
			ret++;
	}
	return ret;
}

int main(void) {
	// �Էº�
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[cur][i][j]);
			if (map[cur][i][j])
				q.push({ i, j });	// �ʱ� ���� ��ġ ����
		}
	}
	// ó����
	while (!q.empty()) {
		int size = q.size();
		int next = (cur + 1) % 2;

		if (cluster() > 1) {	// ������ �� �̻����� �и��� ���
			printf("%d\n", ans); // �ҿ� �ð� ��� ��
			return 0;	// ����
		}
		while (size--) {	// ����(generation) ���� ����
			point p = q.front(); q.pop();
			int cnt = count(p);	// ������ ��� ��
			if (map[cur][p.x][p.y] > cnt) {	// ������ �� ���� ���� ���
				map[next][p.x][p.y] = map[cur][p.x][p.y] - cnt; // map[next]�� ���� ���� ����
				q.push(p);	// ť�� �ٽ� ����
			}
		}
		// ���� �� �ʱ�ȭ
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				map[cur][i][j] = 0;
		cur = next;	// cur�� ���ŵ� ���� �ε����� ������Ʈ
		ans++;	// �ð� ����
	}

	printf("0\n");	// ��� ���� ������ ������ �и����� ����
	return 0;
}