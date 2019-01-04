#include <cstdio>
using namespace std;

bool check[20];
int S[20][20];
int N, ans = 2e9;

int min(int a, int b) { return a <= b ? a : b; }

int calculate(void) {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (check[i] != check[j])
				continue;
			if (check[i])
				ret += S[i][j];
			else
				ret -= S[i][j];
		}
	}
	return ret >= 0 ? ret : -ret;
}

void go(int cur, int n) {
	if (n == N / 2) {
		ans = min(ans, calculate());
		return;
	}
	// nC(n/2) ����
	for (int i = cur; i <= N / 2 + n; i++) {
		check[i] = true;
		go(i + 1, n + 1);
		check[i] = false;
		if (ans == 0)	// 0�� ��� ������ Ž�� ����
			return;
	}
}

int main(void) {
	// �Էº�
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &S[i][j]);
	// ó����
	go(0, 0);
	// ��º�
	printf("%d\n", ans);
	return 0;
}