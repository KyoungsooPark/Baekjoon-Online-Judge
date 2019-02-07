/*
https://www.acmicpc.net/problem/1107
*/

#include <cstdio>
using namespace std;

bool broken[10];

int abs(int num) { return num >= 0 ? num : -num; }

int length(int num) {	// 채널 num의 길이 반환
	int ret = 0;
	if (num == 0) {	// num이 0일 때
		if (broken[0])	// 버튼 0이 고장
			return 0;
		return 1;
	}

	while (num) {
		if (broken[num % 10])
			return 0;
		num /= 10;
		ret++;
	}
	return ret;
}

int main(void) {
	int dst, n, ans;
	// 입력부
	scanf("%d", &dst);
	scanf("%d", &n);
	while (n--) {
		int m;
		scanf("%d", &m);
		broken[m] = true;
	}
	// 처리부
	ans = abs(100 - dst);	// +/- 버튼으로만 이동하는 횟수
	for (int i = 0; i < 999900; i++) {
		int len = length(i);
		if (len) {
			int temp = len + abs(i - dst);	// 채널 i로 이동 후 +/- 버튼으로 이동하는 횟수
			if (ans > temp)
				ans = temp;
		}
	}
	// 출력부
	printf("%d\n", ans);
	return 0;
}