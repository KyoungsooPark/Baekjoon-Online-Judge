#include <cstdio>
#include <queue>
using namespace std;
typedef struct { int x, y; } point;

vector<point> virus;
int map[8][8];
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int N, M, ans;

int max(int a, int b) { return a >= b ? a : b; }

int simulate(void) {
	int cpy[8][8], ret = 0;
	queue<point> q;
	// map ����
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cpy[i][j] = map[i][j];
	// ���̷��� �ʱ� ��ġ q�� ����
	for (const point &p : virus)
		q.push(p);

	while (!q.empty()) {
		point p = q.front();
		q.pop();
		for (int d = 0; d < 4; d++) {
			int nx = p.x + dx[d], ny = p.y + dy[d];
			if (0 <= nx && nx < N && 0 <= ny && ny < M) {
				if (cpy[nx][ny] == 0) {
					cpy[nx][ny] = 2;	// ���̷��� ����
					q.push({ nx, ny });
				}
			}
		}
	}
	// ���� ���� ���
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (cpy[i][j] == 0)
				ret++;
	return ret;
}

void go(int x, int y, int n) {
	map[x][y] = 1;	// �� ��ġ

	if (n == 3) {	// 3���� ���� ��� ��ġ�� ���
		ans = max(ans, simulate());	// �ִ� ���� ���� ��� ��
		map[x][y] = 0;	// �� ����
		return;
	}

	for (int i = x; i < N; i++)
		for (int j = i == x ? y + 1 : 0; j < M; j++)
			if (map[i][j] == 0)	// �� ��ġ ���� ��ġ�� ���
				go(i, j, n + 1);	// ����Լ� ȣ��
	map[x][y] = 0;	// �� ����
}

int main(void) {
	// �Էº�
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 2)
				virus.push_back({ i, j });
		}
	// ó����
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (map[i][j] == 0)
				go(i, j, 1);
	// ��º�
	printf("%d\n", ans);
	return 0;
}