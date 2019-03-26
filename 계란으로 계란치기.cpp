/*
https://www.acmicpc.net/problem/16987
*/

#include <cstdio>
using namespace std;
typedef struct { int S, W; } egg;

egg arr[8];
int N, ans = 0;

int max(int a, int b) { return a >= b ? a : b; }
// 깨진 계란 총 개수 조사
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
	// 손에 든 계란이 깨진 경우
	if (arr[n].S <= 0)
		go(n + 1); // 치지 않고 넘어감
	else {
		bool flag = false; // 깨지지 않은 다른 계란이 있는지 여부 검사 flag
		for (int i = 0; i < N; i++) {
			// 손에 든 것과 같은 계란이 아니고 깨지지 않은 경우
			if (i != n && arr[i].S > 0) {
				flag = true;
				arr[n].S -= arr[i].W, arr[i].S -= arr[n].W;
				go(n + 1);
				arr[n].S += arr[i].W, arr[i].S += arr[n].W;
			}
		}
		// 다른 계란이 모두 깨진 경우
		if (!flag)
			go(n + 1); // 치지 않고 넘어감
	}
}

int main(void) {
	// 입력부
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d %d", &arr[i].S, &arr[i].W);
	// 처리부
	go(0);
	// 출력부
	printf("%d\n", ans);
	return 0;
}