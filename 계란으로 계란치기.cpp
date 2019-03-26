/*
https://www.acmicpc.net/problem/16987
*/

#include <cstdio>
using namespace std;
typedef struct { int S, W; } egg;

egg arr[8];
int N, ans = 0;

int max(int a, int b) { return a >= b ? a : b; }
// ���� ��� �� ���� ����
int count(void) {
	int ret = 0;
	for (int i = 0; i < N; i++)
		if (arr[i].S <= 0)
			ret++;
	return ret;
}

void go(int n) {
	if (n == N) {
		ans = max(ans, count());
		return;
	}
	// �տ� �� ����� ���� ���
	if (arr[n].S <= 0)
		go(n + 1); // ġ�� �ʰ� �Ѿ
	else {
		bool flag = false; // ������ ���� �ٸ� ����� �ִ��� ���� �˻� flag
		for (int i = 0; i < N; i++) {
			// �տ� �� �Ͱ� ���� ����� �ƴϰ� ������ ���� ���
			if (i != n && arr[i].S > 0) {
				flag = true;
				arr[n].S -= arr[i].W, arr[i].S -= arr[n].W;
				go(n + 1);
				arr[n].S += arr[i].W, arr[i].S += arr[n].W;
			}
		}
		// �ٸ� ����� ��� ���� ���
		if (!flag)
			go(n + 1); // ġ�� �ʰ� �Ѿ
	}
}

int main(void) {
	// �Էº�
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d %d", &arr[i].S, &arr[i].W);
	// ó����
	go(0);
	// ��º�
	printf("%d\n", ans);
	return 0;
}