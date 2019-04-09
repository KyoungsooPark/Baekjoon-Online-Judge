/*
https://www.acmicpc.net/problem/17136
*/

#include <cstdio>
#include <queue>
using namespace std;
typedef struct { int x, y; } point;

vector<point> v;	// �����̸� ���ƾ� �ϴ� ��ġ ����
int map[10][10];
int check[6] = { 0, 5, 5, 5, 5, 5 };	// ���� ������ ����
int dx[3] = { 0, 1, 1 };	// ��, ��, ��
int dy[3] = { 1, 0, 1 };	// ��, ��, ��
int ans = 2e9;

int min(int a, int b) { return a < b ? a : b; }
// range ũ���� �����̸� map�� 
void set(point p, int range, int val) {
	for (int i = p.x; i < p.x + range; i++)
		for (int j = p.y; j < p.y + range; j++)
			map[i][j] = val;
	val == 0 ? check[range]-- : check[range]++;
}
// ���� �� �ִ� ������ �ִ� ũ�� ���
int max_range(point p) {
	bool visited[5][5] = { false };	// ���� ��ġ�κ��� �ִ� 5x5 ũ�� ���� �湮 ���� �˻�
	int ret = 1;	// �־��� ��ġ p�� ���� �� �ִ� ������ �ּ� ũ��
	queue<point> q;	// �־��� ��ġ p�κ��� ��, ��, �� Ž��
	q.push(p);
	visited[0][0] = true;

	while (!q.empty()) {
		int size = q.size();
		while (size--) {
			point now = q.front(); q.pop();
			for (int d = 0; d < 3; d++) {
				int nx = now.x + dx[d], ny = now.y + dy[d];
				if (0 <= nx && nx < 10 && 0 <= ny && ny < 10) {
					if (map[nx][ny] && !visited[nx - p.x][ny - p.y]) {
						q.push({ nx, ny });
						visited[nx - p.x][ny - p.y] = true;
					}
				}
			}
		}
		// ex) 2x2 ������ ��� ť�� ���ԵǴ� ��ġ �� = (2 * 1) + 1 = 3
		//     3x3 ������ ��� ť�� ���ԵǴ� ��ġ �� = (2 * 2) + 1 = 3
		//     => n x n : 2n - 1 = 2(n - 1) + 1 = 2(ret) + 1
		if (q.size() != ret * 2 + 1 || ret == 5)	return ret;
		ret++;
	}
}

void go(int i, int n, int total) {
	if (ans < n)	return;	// ��������� best case�� �Ѿ�� ��� Ž�� ����
	if (total == v.size()) {	// ��� ���� Ž�� �Ϸ�
		ans = min(ans, n);
		return;
	}
	if (!map[v[i].x][v[i].y]) {	// �����̰� �̹� ������ ��ġ�� ���
		go(i + 1, n, total);	// ���� ��ġ�� �̵�
		return;
	}
	// ��� ������ ������ �ִ� ũ����� ���� ũ����� Ž��
	for (int r = max_range(v[i]); r > 0; r--) {
		if (check[r]) {	// �ش� ũ���� ������ ������ �����ִ� ���
			set(v[i], r, 0);	// ������ ���
			go(i + 1, n + 1, total + r * r);	// ���� ��ġ Ž��
			set(v[i], r, 1);	// ������ ȸ��
		}
	}
}

int main(void) {
	// �Էº�
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j])	v.push_back({ i, j });
		}
	// ó����
	if (!v.size()) {
		printf("0\n");
		return 0;
	}
	go(0, 0, 0);
	// ��º�
	printf("%d\n", ans == 2e9 ? -1 : ans);
	return 0;
}