/*
https://www.acmicpc.net/problem/16234
*/

#include <cstdio>
#include <queue>
#include <vector>
using namespace std;
typedef struct { int x, y; } point;

bool check[50][50];
int map[50][50], next_map[50][50];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int N, L, R;

int abs(int num) { return num >= 0 ? num : -num; }

bool bfs(void) {
	bool ret = false;
	queue<point> q;
	vector<point> v;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (check[i][j])	continue;
			q.push({ i, j }), v.push_back({ i, j }), check[i][j] = true;
			while (!q.empty()) {
				point p = q.front(); q.pop();
				for (int d = 0; d < 4; d++) {
					int nx = p.x + dx[d], ny = p.y + dy[d];
					if (0 <= nx && nx < N && 0 <= ny && ny < N && !check[nx][ny]) {
						int num = abs(map[p.x][p.y] - map[nx][ny]);
						if (L <= num  && num <= R)	// �ش� ������ �α� �̵��� ������ ���
							q.push({ nx, ny }), v.push_back({ nx, ny }), check[nx][ny] = true;
					}
				}
			}
			if (v.size() > 1) {	// �α� �̵��� ������ ������ �����ϴ� ���
				int temp = 0;
				// �α��� ��� ���
				for (const point &p : v)
					temp += map[p.x][p.y];
				temp /= v.size();
				// ��� �α����� �й�
				for (const point &p : v)
					next_map[p.x][p.y] = temp;
			}
			else	// �α� �̵��� ������ ������ �������� �ʴ� ���
				check[i][j] = false;	// �ش� Ž�� ������ check ���� �ʱ�ȭ
			v.clear();	// �̵� ���� ���� �ʱ�ȭ
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] != next_map[i][j]) {	// �α� �̵��� �־�����
				map[i][j] = next_map[i][j];	// �̵��� �α��� ����
				ret = true;	// �α��� �̵��� �־����� ǥ��
			}
			check[i][j] = false;	// ��� check ���� �ʱ�ȭ
		}
	}
	return ret;
}

int main(void) {
	int ans = 0;
	// �Էº�
	scanf("%d %d %d", &N, &L, &R);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &map[i][j]), next_map[i][j] = map[i][j];

	// ó����
	while (bfs())
		ans++;

	// ��º�
	printf("%d\n", ans);
	return 0;
}