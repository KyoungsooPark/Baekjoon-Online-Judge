/*
https://www.acmicpc.net/problem/15953
*/

#include <cstdio>
using namespace std;

const int unit = 10000;	// ���� ����
int arr1[7] = { 0, 500, 300, 200, 50, 30, 10 };	// arr1[i] = 2017�� i���� ���
int arr2[6] = { 0, 512, 256, 128, 64, 32 };		// arr2[i] = 2018�� i���� ���

int main(void) {
	int T;
	scanf("%d", &T);
	while (T--) {
		int a, b, ans = 0;
		scanf("%d %d", &a, &b);
		// 1��: 1��, 2��: 2��, 3��: 3��, ..., 6��: 6��. �� 21��
		for (int i = 0, sum = 0; i <= 6; i++, sum += i) {
			if (a <= sum) {
				ans += arr1[i];
				break;
			}
		}
		// 1��: 1��, 2��: 2��, 3��: 4��, ..., 5��: 16��. �� 64��
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