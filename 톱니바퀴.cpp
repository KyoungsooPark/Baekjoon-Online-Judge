/*
https://www.acmicpc.net/problem/14891
*/

#include <cstdio>
using namespace std;

int wheel[4][8], top_idx[4];
// wheel_idx ��° ��Ϲ����� ���� �ڼ�
int left_tip(int wheel_idx) {
	int idx = top_idx[wheel_idx] - 2;
	if (idx < 0)
		idx += 8;
	return wheel[wheel_idx][idx];
}
// wheel_idx ��° ��Ϲ����� ������ �ڼ�
int right_tip(int wheel_idx) {
	int idx = top_idx[wheel_idx] + 2;
	if (idx > 7)
		idx -= 8;
	return wheel[wheel_idx][idx];
}
// wheel_idx ��° ��Ϲ����� top ��ġ ����
void change_top(int wheel_idx, int direction) {
	top_idx[wheel_idx] -= direction;
	if (top_idx[wheel_idx] == -1)
		top_idx[wheel_idx] = 7;
	else if (top_idx[wheel_idx] == 8)
		top_idx[wheel_idx] = 0;
}
// ��Ϲ��� ȸ��
void rotate(int wheel_idx, int direction) {
	int dir_info[4];
	dir_info[wheel_idx] = direction;
	// ���� ��Ϲ����� ȸ�� ���� ����
	for (int left = wheel_idx - 1; left >= 0; left--) {
		if (dir_info[left + 1] && right_tip(left) != left_tip(left + 1))
			dir_info[left] = dir_info[left + 1] * (-1);
		else
			dir_info[left] = 0;
	}
	// ������ ��Ϲ����� ȸ�� ���� ����
	for (int right = wheel_idx + 1; right <= 3; right++) {
		if (dir_info[right - 1] && left_tip(right) != right_tip(right - 1))
			dir_info[right] = dir_info[right - 1] * (-1);
		else
			dir_info[right] = 0;
	}
	// ��ü ��Ϲ��� ȸ��
	for (int wh = 0; wh < 4; wh++)
		if (dir_info[wh])
			change_top(wh, dir_info[wh]);
}
// ���� ���
int score(void) {
	int ret = 0;
	for (int wh = 0; wh < 4; wh++) {
		ret += wheel[wh][top_idx[wh]] * (1 << wh);
	}
	return ret;
}

int main(void) {
	int K;
	// �Էº�
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++)
			scanf("%1d", &wheel[i][j]);
		top_idx[i] = 0;
	}
	scanf("%d", &K);

	// ó����
	while (K--) {
		int wh, d;
		scanf("%d %d", &wh, &d);
		rotate(wh - 1, d);
	}

	//��º�
	printf("%d\n", score());
	return 0;
}