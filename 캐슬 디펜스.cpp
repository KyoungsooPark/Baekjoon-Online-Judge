/*
https://www.acmicpc.net/problem/17135
*/

#include <iostream>
#include <vector>
using namespace std;
struct point { int x, y; };

point archer[3];	// �ü�
bool map[15][15];	// ���� �ʱ� ����
bool cpy[15][15];	// �ùķ��̼��� ���� ī�� ��
int N, M, D, ans = 0;

int abs(int num) { return num < 0 ? -num : num; }
int max(int a, int b) { return a > b ? a : b; }
// �ü��� ��ġ (x, y)�κ��� ���� ������ �� Ž��
point search(point p) {
	point ret = { -1, -1 };	// ��ȯ�� ���� ��ġ
	int tempD = D + 1;	// ��Ÿ� �� ���� ����� ������ �Ÿ��� ����ϱ� ���� ����
	for (int x = N - D; x < N; x++) {
		for (int y = p.y - D + 1; y < p.y + D; y++) {
			if (0 <= y && y < M && cpy[x][y]) {	// Ž�� ������ ���� ����
				int temp = abs(p.x - x) + abs(p.y - y);	// ������ �Ÿ� ���
				if (tempD > temp) {	// ��Ÿ� D �̳� �Ǵ� �� ����� ���� ���
					ret = { x, y };	// �� ��ġ ����
					tempD = temp;	// �ش� ������ �Ÿ� ����
				}
				else if (tempD == temp && y < ret.y)	// ���� �Ÿ����� �� ������ �� �߰�
					ret = { x, y };	// �ش� �� ��ġ ����
			}
		}
	}
	return ret;	// Ž�� ����� �������� �ʴ� ��� { -1, -1 } ��ȯ, �����ϴ� ��� �ش� ���� ��ġ ��ȯ
}

void simulation(void) {
	bool flag = true;	// �� ���� ����
	int killed = 0;	// ������ ���� ����
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cpy[i][j] = map[i][j];
	while (flag) {
		vector<point> v;	// ������ ���� ������ ����
		flag = false;	// flag ����
		for (int i = 0; i < 3; i++) {	// �� ������ �ü��� ����
			point p = search(archer[i]);	// ������ �� Ž��
			if (p.x != -1)	// Ž�� ��� ���� ����� �����ϴ� ���
				v.push_back({ p.x, p.y });	// ���Ϳ� ���� (���� �ٸ� �� �ü��� Ÿ���� �ߺ��� �� ����)
		}
		// ���� ������ �� ����
		for (int i = 0; i < v.size(); i++) {
			if (cpy[v[i].x][v[i].y]) {	// �ش� ��ġ�� ���� �����ϸ�(�ߺ��Ǵ� ���� ��� �̹� ���ŵǾ��� �� ����)
				cpy[v[i].x][v[i].y] = false;	// �ش� ���� �ʿ��� ����
				killed++;	// ������ ���� �� ����
			}
		}
		// �� ����
		for (int i = N - 1; i > 0; i--)
			for (int j = 0; j < M; j++) {
				cpy[i][j] = cpy[i - 1][j];
				if (cpy[i][j])	// ���� ���� ����
					flag = true;	// flag ��
			}
		for (int j = 0; j < M; j++)	// ���� �� �� �ʱ�ȭ
			cpy[0][j] = false;
	}
	ans = max(ans, killed);	//  ������ ���� �ִ� �� ������Ʈ
}

void go(int n, int cur) {
	if (n == 3) {
		simulation();
		return;
	}
	for (int i = cur; i < M; i++) {
		archer[n] = { N, i };
		go(n + 1, i + 1);
	}
}

int main(void) {
	// �Էº�
	scanf("%d %d %d", &N, &M, &D);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> map[i][j];
	// ó����
	go(0, 0);
	// ��º�
	setbuf(stdout, NULL);
	printf("%d\n", ans);
	return 0;
}