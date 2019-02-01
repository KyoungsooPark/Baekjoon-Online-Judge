/*
https://www.acmicpc.net/problem/11723
*/

#include <cstdio>
#include <cstring>
using namespace std;

int main(void) {
	int M, x, S = 0;	// 4 byte = 32 bit 이므로 1 ~ 20 까지의 수를 bit로 표현 가능
	char cmd[7];
	scanf("%d", &M);
	while (M--) {
		scanf("%s", &cmd);
		if (!strcmp(cmd, "add")) {
			scanf("%d", &x);
			S |= (1 << x);	// 2^(x)와 S를 OR 연산
		}
		else if (!strcmp(cmd, "remove")) {
			scanf("%d", &x);
			S &= ~(1 << x);	// 2^(x)의 보수와 S를 AND 연산
		}
		else if (!strcmp(cmd, "check")) {
			scanf("%d", &x);
			printf("%d\n", S & (1 << x) ? 1 : 0);	// 2^(x)와 S의 AND 연산으로 검사
		}
		else if (!strcmp(cmd, "toggle"))
			S ^= (1 << x);	// // 2^(x)와 S를 XOR 연산
		else if (!strcmp(cmd, "all"))
			S = (1 << 21) - 1;	// 2^(21) - 1 을 통해 2^(20)번째 bit까지 모두 체크
		else if (!strcmp(cmd, "empty"))
			S = 0;
	}
	return 0;
}