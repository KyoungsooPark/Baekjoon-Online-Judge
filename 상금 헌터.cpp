/*
https://www.acmicpc.net/problem/15953
*/

#include <cstdio>
using namespace std;

const int unit = 10000;	// 만원 단위
int arr1[7] = { 0, 500, 300, 200, 50, 30, 10 };	// arr1[i] = 2017년 i등의 상금
int arr2[6] = { 0, 512, 256, 128, 64, 32 };		// arr2[i] = 2018년 i등의 상금

int main(void) {
	int T;
	scanf("%d", &T);
	while (T--) {
		int a, b, ans = 0;
		scanf("%d %d", &a, &b);
		// 1등: 1명, 2등: 2명, 3등: 3명, ..., 6등: 6명. 총 21명
		for (int i = 0, sum = 0; i <= 6; i++, sum += i) {
			if (a <= sum) {
				ans += arr1[i];
				break;
			}
		}
		// 1등: 1명, 2등: 2명, 3등: 4명, ..., 5등: 16명. 총 64명
		for (int i = 0; i <= 6; i++) {
			if (b < (1 << i)) {
				ans += arr2[i];
				break;
			}
		}
		printf("%d\n", ans * unit);
	}
	return 0;
}