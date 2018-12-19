/*
https://www.acmicpc.net/problem/14501
*/

#include <cstdio>
using namespace std;

int d[16];

int max(int a, int b) { return a >= b ? a : b; }

int main(void) {
	int N, T[15], P[15];
	// �Էº�
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d %d", &T[i], &P[i]);
	// ó����
	for (int i = 0; i < N; i++) {
		d[i + 1] = max(d[i], d[i + 1]);
		if (i + T[i] <= N)
			d[i + T[i]] = max(d[i + T[i]], d[i] + P[i]);
	}
	// ��º�
	printf("%d\n", d[N]);
	return 0;
}