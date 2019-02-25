/*
https://www.acmicpc.net/problem/14891
*/

#include <cstdio>
#include <deque>
#define L	6
#define R	2
using namespace std;

deque<bool> wheel[4];
int K;

void rotate(int idx, int dir) {	// ��Ϲ��� ȸ��
	if (dir == -1) {	// �ݽð���� ȸ��
		bool front = wheel[idx].front();
		wheel[idx].pop_front();
		wheel[idx].push_back(front);
	}
	else if (dir == 1) {	// �ð���� ȸ��
		bool back = wheel[idx].back();
		wheel[idx].pop_back();
		wheel[idx].push_front(back);
	}
}

int main(void) {
	int ans = 0;
	// �Էº�
	for (int i = 0; i < 4; i++) {
		wheel[i].assign(8, false);
		for (int j = 0; j < 8; j++)
			scanf("%1d", &wheel[i][j]);
	}
	scanf("%d", &K);

	// ó����
	while (K--) {
		int idx, dir, dir_arr[4] = { 0, };
		scanf("%d %d", &idx, &dir);
		dir_arr[--idx] = dir;
		// ���� ��Ϲ����� ȸ�� �˻�
		for (int i = idx - 1; i >= 0; i--)
			if (wheel[i][R] != wheel[i + 1][L])
				dir_arr[i] = dir_arr[i + 1] * (-1);
		// ������ ��Ϲ����� ȸ�� �˻�
		for (int i = idx + 1; i < 4; i++)
			if (wheel[i][L] != wheel[i - 1][R])
				dir_arr[i] = dir_arr[i - 1] * (-1);
		// ��ü ��Ϲ��� ȸ��
		for (int i = 0; i < 4; i++)
			rotate(i, dir_arr[i]);
	}
	
	// ��º�
	for (int i = 0; i < 4; i++)
		if (wheel[i][0])
			ans += (1 << i);
	printf("%d\n", ans);
	return 0;
}