/*
https://www.acmicpc.net/problem/1021
*/

#include <cstdio>
#include <deque>
using namespace std;

deque<int> dq;
int N, M;

int index(int num) {	// dq���� num�� �ε��� ��ȯ
	int idx = 0;
	while (dq[++idx] != num);
	return idx;
}

int main(void) {
	int num, ans = 0;

	// �Էº�
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++)
		dq.push_back(i);

	// ó����
	for (int i = 0; i < M; i++) {
		scanf("%d", &num);

		if (dq.front() != num) {
			int idx = index(num);
			if (idx <= dq.size() / 2) {	// N = 11, num = 6�� ��츦 �����غ���
				// left shift
				while (dq.front() != num) {
					int front = dq.front();	// front��
					dq.pop_front();			// pop�ؼ�
					dq.push_back(front);	// back�� push
					ans++;
				}
			}
			else {
				// right shift
				while (dq.front() != num) {
					int back = dq.back();	// back��
					dq.pop_back();			// pop�ؼ�
					dq.push_front(back);	// front�� push
					ans++;
				}
			}
		}
		dq.pop_front();
	}

	// ��º�
	printf("%d\n", ans);
	return 0;
}