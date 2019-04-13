/*
https://www.acmicpc.net/problem/17136
*/

#include <iostream>
#include <vector>
using namespace std;
struct point { int x, y; };

vector<point> v;	// �����̸� ���ƾ� �ϴ� ��ġ ����
bool map[10][10];
int cnt[6] = { 0, 5, 5, 5, 5, 5 };	// ���� ������ ����
int ans = 2e9;

int min(int a, int b) { return a < b ? a : b; }
// ���� �� �ִ� ������ �ִ� ũ�� ���
// �˻� ���� r�� ������Ű�� ������, �Ʒ� �׵θ� �˻�
// ex) (x, y)���� 2x2 �˻� => (x, y + 1), (x + 1, y + 1), (x, y + 1) �˻�
int max_range(point p) {
	int r;
	for (r = 1; r < 5; r++) {
		for (int x = p.x; x <= p.x + r; x++)
			if (x > 9 || p.y + r > 9 || !map[x][p.y + r])
				return r;
		for (int y = p.y; y < p.y + r; y++)
			if (p.x + r > 9 || y > 9 || !map[p.x + r][y])
				return r;
	}
	return r;
}
// range ũ���� �����̸� map�� ��� �Ǵ� ȸ��
void set(point p, int range, bool val) {
	for (int x = p.x; x < p.x + range; x++)
		for (int y = p.y; y < p.y + range; y++)
			map[x][y] = val;
	val ? cnt[range]++ : cnt[range]--;	// false�� ��� ���, true�� ��� ȸ��
}

void go(int idx, int n, int total) {
	if (total == v.size()) {	// ��� ���� Ž�� �Ϸ�
		ans = min(ans, n);
		return;
	}
	if (ans == n)	return;	// ��������� best case�� �Ѿ�� ��� Ž�� ����
	if (!map[v[idx].x][v[idx].y]) {	// �����̰� �̹� ������ ��ġ�� ���
		go(idx + 1, n, total);	// ���� ��ġ�� �̵�
		return;
	}
	// ��� ������ ������ �ִ� ũ����� ���� ũ����� Ž��
	for (int r = max_range(v[idx]); r > 0; r--) {
		if (cnt[r]) {	// �ش� ũ���� ������ ������ �����ִ� ���
			set(v[idx], r, false);	// ������ ���
			go(idx + 1, n + 1, total + r * r);	// ���� ��ġ Ž��
			set(v[idx], r, true);	// ������ ȸ��
		}
	}
}

int main(void) {
	// �Էº�
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++) {
			cin >> map[i][j];
			if (map[i][j])
				v.push_back({ i, j });
		}
	// ó����
	go(0, 0, 0);
	// ��º�
	printf("%d\n", ans == 2e9 ? -1 : ans);
	return 0;
}