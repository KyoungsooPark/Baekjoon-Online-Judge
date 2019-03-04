/*
https://www.acmicpc.net/problem/14889
*/

#include <cstdio>
using namespace std;

bool check[20];
int S[20][20];
int N, ans = 2e9;

int min(int a, int b) { return a <= b ? a : b; }
int abs(int num) { return num >= 0 ? num : -num; }

int calculate(void) {
	int start = 0, link = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (check[i] && check[j])
				start += S[i][j];
			else if (!check[i] && !check[j])
				link += S[i][j];
		}
	}
	return abs(start - link);
}

void go(int n, int cur) {
	if (n == N / 2) {
		ans = min(ans, calculate());
		return;
	}
	for (int i = cur; i <= N / 2 + n; i++) {	// N_Combination_(N/2)
		check[i] = true;
		go(n + 1, i + 1);
		check[i] = false;
		if (ans == 0) return;	// 차이가 0인 경우 더 탐색하지 않고 종료
	}
}

int main(void) {
	// 입력부
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &S[i][j]);
	// 처리부
	go(0, 0);
	// 출력부
	printf("%d\n", ans);
	return 0;
}
