/*
https://www.acmicpc.net/problem/9095
*/

#include <cstdio>
using namespace std;

int d[11] = { 0, 1, 2, 4 };

int go(int n) {
	if (d[n])
		return d[n];
	return d[n] = go(n - 1) + go(n - 2) + go(n - 3);
}

int main(void) {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		printf("%d\n", go(n));
	}
	return 0;
}