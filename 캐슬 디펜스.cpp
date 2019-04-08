/*
https://www.acmicpc.net/problem/17135
*/

#include <cstdio>
#include <queue>
#include <vector>
using namespace std;
typedef struct { int x, y; } point;

queue<point> q;		// ���� ��ġ ���� �� ������ �ùķ��̼��� ���� ť
point archer[3];	// �ü�
int map[15][15];	// ���� �ʱ� ����
int cpy[15][15];	// �ùķ��̼��� ���� ī�� ��
int cpy_next[15][15];	// ī�� ���� ���� ���¸� �����ϱ� ���� �ӽ� ��
int N, M, D, ans = 0;

int max(int a, int b) { return a > b ? a : b; }
int abs(int num) { return num >= 0 ? num : -num; }
// �ü��� ��ġ (x, y)�κ��� ���� ������ �� Ž��
point search(int x, int y) {
	point ret = { -1, -1 };	// ��ȯ�� ���� ��ġ
	int tempD = D + 1;	// ��Ÿ� �� ���� ����� ������ �Ÿ��� ����ϱ� ���� ����
	for (int i = x - D; i < x; i++) {
		for (int j = y - D + 1; j <= y + D - 1; j++) {
			if (0 <= j && j < M && cpy[i][j]) {	// Ž�� ������ ���� ����
				int temp = abs(x - i) + abs(y - j);	 // ������ �Ÿ� ���
				if (tempD > temp) {	// ��Ÿ� D �̳� �Ǵ� �� ����� ���� ���
					ret = { i, j };	// �� ��ġ ����
					tempD = temp;	// �ش� ������ �Ÿ� ����
				}
				else if (tempD == temp) {	// ������� ���� ����� ������ �Ÿ��� ���� �Ÿ��� �� �߰�
					if (ret.y > j)	// �� ������ ���� ���
						ret = { i, j };	// �ش� �� ��ġ ����
				}
			}
		}
	}
	// Ž�� ����� �������� �ʴ� ��� { -1, -1 } ��ȯ, �����ϴ� ��� �ش� ���� ��ġ ��ȯ
	return ret;
}

int simulation(void) {
	int killed = 0;	// ������ ���� ����
	// �� ī��
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			cpy[i][j] = map[i][j];
			if (map[i][j])
				q.push({ i, j });	// ���� ��ġ ť�� ����
		}

	while (!q.empty()) {
		vector<point> v;	// ������ ���� ������ ����
		for (int i = 0; i < 3; i++) {	// �� ������ �ü��� ����
			point p = search(archer[i].x, archer[i].y);	// ������ �� Ž��
			if (p.x != -1)	// Ž�� ��� ���� ����� �����ϴ� ���
				v.push_back(p);	// ���Ϳ� ���� (���� �ٸ� �� �ü��� Ÿ���� �ߺ��� �� ����)
		}
		// ���� ������ �� ����
		for (int i = 0; i < v.size(); i++)
			if (cpy[v[i].x][v[i].y]) {	// �ش� ��ġ�� ���� �����ϸ�(�ߺ��Ǵ� ���� ��� �̹� ���ŵǾ��� �� ����)
				killed++;	// ������ ���� �� ����
				cpy[v[i].x][v[i].y] = 0;	// �ش� ���� �ʿ��� ����
			}
		int size = q.size();	// ��ü ���� �ϰ������� �����̱� ���� ����
		while (size--) {
			point p = q.front(); q.pop();
			if (cpy[p.x][p.y]) {	// �ü����� ���ŵ��� ���� ���
				p.x++;	// ���� �ִ� ��ġ�� �� ĭ ����
				if (p.x < N) {	// ������ �������� ���� ���
					cpy_next[p.x][p.y] = 1;	// ���� ���� ��(cpy_next �迭)�� �ش� �� ǥ��
					q.push(p);	// ť�� ����
				}
			}
		}
		// cpy �ʿ� cpy_next ���� �� cpy_next �ʱ�ȭ
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				cpy[i][j] = cpy_next[i][j], cpy_next[i][j] = 0;
	}
	return killed;	// ������ ���� ���� ��ȯ
}

void go(int n, int cur) {
	if (n == 3) {
		ans = max(ans, simulation());
		return;
	}
	for (int i = cur; i < M; i++) {
		archer[n] = { N, i };
		go(n + 1, cur + 1);
	}
}

int main(void) {
	// �Էº�
	scanf("%d %d %d", &N, &M, &D);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			scanf("%d", &map[i][j]);
	// ó����
	go(0, 0);
	// ��º�
	setbuf(stdout, NULL);
	printf("%d\n", ans);
	return 0;
}