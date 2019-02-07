/*
https://www.acmicpc.net/problem/9019
*/

#include <cstdio>
#include <cstring>
#define MAX	10000
using namespace std;

bool check[MAX];
char how[MAX];
int from[MAX];
int q[MAX];
int begin, end;
int A, B;
char dslr[4] = { 'D', 'S', 'L', 'R' };

void push(int num) { q[end++] = num; }
int pop(void) { return q[begin++]; }

void print(int src, int dst) {
	if (src != from[dst])
		print(src, from[dst]);
	printf("%c", how[dst]);
}

int main(void) {
	int T;
	scanf("%d", &T);
	while (T--) {
		// 입력부
		scanf("%d %d", &A, &B);

		// 처리부
		begin = end = 0;	// queue 초기화
		check[A] = true;
		push(A);
		while (!check[B]) {
			int now = pop();
			int temp[4] = {
				now * 2 % MAX,						// D
				now ? now - 1 : 9999,				// S
				(now % 1000) * 10 + (now / 1000),	// L
				(now / 10) + (now % 10) * 1000 };	// R

			for (int i = 0; i < 4; i++) {
				int next = temp[i];
				if (!check[next]) {
					check[next] = true;
					from[next] = now;
					how[next] = dslr[i];
					push(next);
				}
			}
		}

		// 출력부
		print(A, B);
		printf("\n");
		memset(check, false, sizeof(check));	// check 초기화
	}
	return 0;
}