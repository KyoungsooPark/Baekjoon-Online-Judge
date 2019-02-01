/*
https://www.acmicpc.net/problem/11723
*/

#include <cstdio>
#include <cstring>
using namespace std;

int main(void) {
	int M, x, S = 0;	// 4 byte = 32 bit �̹Ƿ� 1 ~ 20 ������ ���� bit�� ǥ�� ����
	char cmd[7];
	scanf("%d", &M);
	while (M--) {
		scanf("%s", &cmd);
		if (!strcmp(cmd, "add")) {
			scanf("%d", &x);
			S |= (1 << x);	// 2^(x)�� S�� OR ����
		}
		else if (!strcmp(cmd, "remove")) {
			scanf("%d", &x);
			S &= ~(1 << x);	// 2^(x)�� ������ S�� AND ����
		}
		else if (!strcmp(cmd, "check")) {
			scanf("%d", &x);
			printf("%d\n", S & (1 << x) ? 1 : 0);	// 2^(x)�� S�� AND �������� �˻�
		}
		else if (!strcmp(cmd, "toggle"))
			S ^= (1 << x);	// // 2^(x)�� S�� XOR ����
		else if (!strcmp(cmd, "all"))
			S = (1 << 21) - 1;	// 2^(21) - 1 �� ���� 2^(20)��° bit���� ��� üũ
		else if (!strcmp(cmd, "empty"))
			S = 0;
	}
	return 0;
}