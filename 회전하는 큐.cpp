/*
https://www.acmicpc.net/problem/1021
*/

#include <cstdio>
#include <deque>
using namespace std;

deque<int> dq;
int N, M;

int index(int num) {	// dq에서 num의 인덱스 반환
	int idx = 0;
	while (dq[++idx] != num);
	return idx;
}

int main(void) {
	int num, ans = 0;

	// 입력부
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++)
		dq.push_back(i);

	// 처리부
	for (int i = 0; i < M; i++) {
		scanf("%d", &num);

		if (dq.front() != num) {
			int idx = index(num);
			if (idx <= dq.size() / 2) {	// N = 11, num = 6인 경우를 생각해보자
				// left shift
				while (dq.front() != num) {
					int front = dq.front();	// front를
					dq.pop_front();			// pop해서
					dq.push_back(front);	// back에 push
					ans++;
				}
			}
			else {
				// right shift
				while (dq.front() != num) {
					int back = dq.back();	// back을
					dq.pop_back();			// pop해서
					dq.push_front(back);	// front에 push
					ans++;
				}
			}
		}
		dq.pop_front();
	}

	// 출력부
	printf("%d\n", ans);
	return 0;
}