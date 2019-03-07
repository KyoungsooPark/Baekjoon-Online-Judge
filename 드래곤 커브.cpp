/*
https://www.acmicpc.net/problem/15685
*/

#include <cstdio>
#include <vector>
using namespace std;

bool map[101][101];
int dx[4] = { 0, -1, 0, 1 };	// ��, ��, ��, ��
int dy[4] = { 1, 0, -1, 0 };	// ��, ��, ��, ��
int N, ans = 0;

void dragon_curve(int x, int y, int d, int g) {
	// �巡�� Ŀ�� ���� �ϼ�
	vector<int> v;	// �巡�� Ŀ�� ���� ���� ����
	v.push_back(d);	// 0���� �巡�� Ŀ�� ����
	for (int i = 1; i <= g; i++)	// i: 1 ~ g����
		for (int j = v.size() - 1; j >= 0; j--)	// j: ������ ���� �ε���
			v.push_back((v[j] + 1) % 4);	// i���� ������ 0 ~ (i - 1)���� ������ ������ +1
	// �巡�� Ŀ�� ǥ��
	map[x][y] = true;
	for (int d : v) {
		x += dx[d], y += dy[d];
		if (0 <= x && x <= 100 && 0 <= y && y <= 100)	// ��ȿ ��ǥ: 0 <= x, y <= 100
			map[x][y] = true;
	}
}

int main(void) {
	// �Էº�
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		int x, y, d, g;
		scanf("%d %d %d %d", &y, &x, &d, &g);
		dragon_curve(x, y, d, g);
	}
	// ó����
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			// �� �������� ��� �巡�� Ŀ���� �Ϻ��� 1 x 1 ���簢�� ���� ī��Ʈ
			if (map[i][j] && map[i][j + 1] && map[i + 1][j] && map[i + 1][j + 1])
				ans++;
	// ��º�
	printf("%d\n", ans);
	return 0;
}