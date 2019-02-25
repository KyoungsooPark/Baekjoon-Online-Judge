/*
https://www.acmicpc.net/problem/14891
*/

#include <cstdio>
#include <deque>
#define L	6
#define R	2
using namespace std;

deque<bool> wheel[4];
int K;

void rotate(int idx, int dir) {	// 톱니바퀴 회전
	if (dir == -1) {	// 반시계방향 회전
		bool front = wheel[idx].front();
		wheel[idx].pop_front();
		wheel[idx].push_back(front);
	}
	else if (dir == 1) {	// 시계방향 회전
		bool back = wheel[idx].back();
		wheel[idx].pop_back();
		wheel[idx].push_front(back);
	}
}

int main(void) {
	int ans = 0;
	// 입력부
	for (int i = 0; i < 4; i++) {
		wheel[i].assign(8, false);
		for (int j = 0; j < 8; j++)
			scanf("%1d", &wheel[i][j]);
	}
	scanf("%d", &K);

	// 처리부
	while (K--) {
		int idx, dir, dir_arr[4] = { 0, };
		scanf("%d %d", &idx, &dir);
		dir_arr[--idx] = dir;
		// 왼쪽 톱니바퀴의 회전 검사
		for (int i = idx - 1; i >= 0; i--)
			if (wheel[i][R] != wheel[i + 1][L])
				dir_arr[i] = dir_arr[i + 1] * (-1);
		// 오른쪽 톱니바퀴의 회전 검사
		for (int i = idx + 1; i < 4; i++)
			if (wheel[i][L] != wheel[i - 1][R])
				dir_arr[i] = dir_arr[i - 1] * (-1);
		// 전체 톱니바퀴 회전
		for (int i = 0; i < 4; i++)
			rotate(i, dir_arr[i]);
	}
	
	// 출력부
	for (int i = 0; i < 4; i++)
		if (wheel[i][0])
			ans += (1 << i);
	printf("%d\n", ans);
	return 0;
}