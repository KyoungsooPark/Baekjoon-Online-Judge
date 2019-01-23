/*
https://www.acmicpc.net/problem/15954
*/

#include <cstdio>
#include <cmath>
using namespace std;

int arr[500], N, K;
// 표준편차 계산
double stdev(int from, int len) {
	double m = 0, v = 0;
	for (int i = from; i < from + len; i++)
		m += arr[i];
	m /= len;
	for (int i = from; i < from + len; i++)
		v += pow(arr[i] - m, 2);
	v /= len;
	return sqrt(v);
}

int main(void) {
	double ans = 2e9;
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++)
		scanf("%d", &arr[i]);
	for (int k = K; k <= N; k++) {
		for (int i = 0; i <= N - k; i++) {
			double temp = stdev(i, k);
			if (ans > temp)
				ans = temp;
		}
	}
	printf("%.11f\n", ans);
	return 0;
}