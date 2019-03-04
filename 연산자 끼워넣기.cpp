/*
https://www.acmicpc.net/problem/14888
*/

#include <cstdio>
using namespace std;
enum { SUM, SUB, MUL, DIV };

int num_arr[11], opt_cnt[4], opt_arr[10];
int N, M = -1e9, m = 1e9;

int max(int a, int b) { return a >= b ? a : b; }
int min(int a, int b) { return a <= b ? a : b; }

int calculate(void) {
	int ret = num_arr[0];
	for (int i = 0; i < N - 1; i++) {
		switch (opt_arr[i]) {
		case SUM: ret += num_arr[i + 1]; break;
		case SUB: ret -= num_arr[i + 1]; break;
		case MUL: ret *= num_arr[i + 1]; break;
		case DIV: ret /= num_arr[i + 1]; break;
		}
	}
	return ret;
}

void go(int n) {
	if (n == N - 1) {	// 모든 연산자 선택 완료
		int temp = calculate();	// 결과 계산
		M = max(M, temp), m = min(m, temp);
		return;
	}

	for (int i = 0; i < 4; i++) {	// 네 가지 연산자 중 택일
		if (opt_cnt[i]) {	// 해당 연산자가 남아있는 경우
			opt_cnt[i]--;	// 개수 차감
			opt_arr[n] = i;	// n번째 자리에 해당 연산자 선택
			go(n + 1);	// 다음 순서 진행
			opt_cnt[i]++;	// 연산자 반환
		}
	}
}

int main(void) {
	// 입력부
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &num_arr[i]);
	for (int i = 0; i < 4; i++)
		scanf("%d", &opt_cnt[i]);
	// 처리부
	go(0);
	// 출력부
	printf("%d\n%d\n", M, m);
	return 0;
}
