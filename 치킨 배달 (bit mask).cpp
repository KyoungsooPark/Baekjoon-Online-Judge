/*
https://www.acmicpc.net/problem/15686
*/

#include <cstdio>
#include <vector>
using namespace std;
typedef struct { int x, y; } point;

vector<point> house, chicken, selected;
int map[50][50];
int N, M, ans = 2e9;

int min(int a, int b) { return a <= b ? a : b; }
int abs(int num) { return num >= 0 ? num : -num; }
int distance(point a, point b) { return abs(a.x - b.x) + abs(a.y - b.y); }

void calculate(void) {	// ������ M�� ġŲ���� ġŲ �Ÿ� ���
	int sum = 0;
	for (point h : house) {
		int temp = 2e9;
		for (point c : selected)
			temp = min(temp, distance(h, c));
		sum += temp;
	}
	ans = min(ans, sum);
}

int main(void) {
	// �Էº�
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 1)
				house.push_back({ i, j });
			else if (map[i][j] == 2)
				chicken.push_back({ i, j });
		}
	// ó����
	for (int i = 0; i < (1 << chicken.size()); i++) {
		// i: ��ü ġŲ�� ���տ��� �κ������� ���� ����
		// e.g.) i = 11 = 1011(2) <- 0, 1, 3��° ġŲ�� ���� (2^0, 2^1, 2^3��° bit�� 1�̹Ƿ�)
		// e.g.) ġŲ�� ���� �� 7���̰� i = (1 << 7) - 1 �̸�,
		//       (1 << 7) - 1 = 10000000(2) - 1 = 01111111(2) <- 0 ~ 6��°(7��) ġŲ�� ����
		for (int j = 0; j < chicken.size(); j++) {
			// j: ����(= i)�� ���Ե� ġŲ���� �ε��� Ž��
			if (i & (1 << j))
				selected.push_back(chicken[j]);
		}
		// M���� ġŲ���� ���õ� ��� ġŲ �Ÿ� ���
		if (selected.size() == M)
			calculate();
		selected.clear();
	}
	// ��º�
	printf("%d\n", ans);
	return 0;
}