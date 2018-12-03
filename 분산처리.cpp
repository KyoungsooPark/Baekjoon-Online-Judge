/*
https://www.acmicpc.net/problem/1009
*/

#include <cstdio>
using namespace std;

int cal(int base, int index) {
	// ���ڸ� ���ϸ� mod ���ִ� ���� nȸ �ݺ�
	// a^(2n) = (a^n)^2 �̶�� ���� ����
	int ret = 1;
	while (index) {
		if (index & 1)
			ret = ret * base % 10;
		base = base * base % 10;
		index >>= 1;
	}
	return ret;
}

int main(void) {
	int T;
	scanf("%d", &T);
	while (T--) {
		int a, b, num;
		// �Էº�
		scanf("%d %d", &a, &b);
		// ó����
		num = cal(a, b);
		num = num == 0 ? 10 : num;
		// ��º�
		printf("%d\n", num);
	}
	return 0;
}