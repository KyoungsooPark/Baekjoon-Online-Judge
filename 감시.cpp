/*
https://www.acmicpc.net/problem/15683
*/

#include <cstdio>
#include <queue>
using namespace std;
typedef struct { int x, y; } point;

vector<point> cctv;
int map[8][8], cpy[8][8], dir[8];
int dx[4] = { 0, 0, -1, 1 };	// 좌, 우, 상, 하
int dy[4] = { 1, -1, 0, 0 };	// 좌, 우, 상, 하
int N, M, ans = 2e9;

int min(int a, int b) { return a <= b ? a : b; }

void one(int x, int y, int d) {
	while (true) {
		x += dx[d], y += dy[d];
		if (x < 0 || N <= x || y < 0 || M <= y) return;	// map을 벗어나는 경우
		if (cpy[x][y] == 6) return;	// 벽이 존재하는 경우
		if (cpy[x][y] == 0)	// 빈 칸인 경우
			cpy[x][y] = -1; // 감시 가능 체크
	}
}

void two(int x, int y, int d) {
	switch (d) {
	case 0: one(x, y, 0); one(x, y, 1); break;	// 좌, 우
	case 1: one(x, y, 2); one(x, y, 3); break;	// 상, 하
	}
}

void three(int x, int y, int d) {
	switch (d) {
	case 0: one(x, y, 0); one(x, y, 2); break;	// 우, 상
	case 1: one(x, y, 0); one(x, y, 3); break;	// 우, 하
	case 2: one(x, y, 1); one(x, y, 2); break;	// 좌, 상
	case 3: one(x, y, 1); one(x, y, 3); break;	// 좌, 하
	}
}

void four(int x, int y, int d) {
	for (int i = 0; i < 4; i++)
		if (i != d)	// d를 제외한 나머지 세 방향
			one(x, y, i);
}

void five(int x, int y) {
	for (int i = 0; i < 4; i++)
		one(x, y, i);	// 네 방향
}

int calculate(void) {
	int ret = 0;
	// map 복사
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cpy[i][j] = map[i][j];
	// 모든 cctv와 해당 dir에 대해 검사
	for (int i = 0; i < cctv.size(); i++) {
		switch (map[cctv[i].x][cctv[i].y]) {
		case 1: one(cctv[i].x, cctv[i].y, dir[i]); break;
		case 2: two(cctv[i].x, cctv[i].y, dir[i]); break;
		case 3: three(cctv[i].x, cctv[i].y, dir[i]); break;
		case 4: four(cctv[i].x, cctv[i].y, dir[i]); break;
		case 5: five(cctv[i].x, cctv[i].y); break;
		}
	}
	// 사각지대 카운트
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (cpy[i][j] == 0)
				ret++;
	return ret;
}

void go(int n) {
	if (n == cctv.size()) {
		ans = min(ans, calculate());
		return;
	}
	int num_case;
	switch (map[cctv[n].x][cctv[n].y]) {
	case 2: num_case = 2; break;	// cctv 2는 상/하 또는 좌/우 두 가지 케이스
	case 5: num_case = 1; break;	// cctv 5는 항상 네 방향이므로 한 가지 케이스
	default: num_case = 4;			// 나머지 cctv는 네 가지 케이스
	}
	for (int d = 0; d < num_case; d++) {
		dir[n] = d;
		go(n + 1);
		if (ans == 0)
			return;
	}
}

int main(void) {
	// 입력부
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
			if (0 < map[i][j] && map[i][j] < 6)
				cctv.push_back({ i, j });
		}
	// 처리부
	go(0);
	// 출력부
	printf("%d\n", ans);
	return 0;
}