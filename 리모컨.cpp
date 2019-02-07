/*
https://www.acmicpc.net/problem/1107
*/

#include <cstdio>
using namespace std;

bool broken[10];

int abs(int num) { return num >= 0 ? num : -num; }

int length(int num) {	// ä�� num�� ���� ��ȯ
	int ret = 0;
	if (num == 0) {	// num�� 0�� ��
		if (broken[0])	// ��ư 0�� ����
			return 0;
		return 1;
	}

	while (num) {
		if (broken[num % 10])
			return 0;
		num /= 10;
		ret++;
	}
	return ret;
}

int main(void) {
	int dst, n, ans;
	// �Էº�
	scanf("%d", &dst);
	scanf("%d", &n);
	while (n--) {
		int m;
		scanf("%d", &m);
		broken[m] = true;
	}
	// ó����
	ans = abs(100 - dst);	// +/- ��ư���θ� �̵��ϴ� Ƚ��
	for (int i = 0; i < 999900; i++) {
		int len = length(i);
		if (len) {
			int temp = len + abs(i - dst);	// ä�� i�� �̵� �� +/- ��ư���� �̵��ϴ� Ƚ��
			if (ans > temp)
				ans = temp;
		}
	}
	// ��º�
	printf("%d\n", ans);
	return 0;
}