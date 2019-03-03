/*
https://www.acmicpc.net/problem/15683
*/

#include <cstdio>
#include <vector>
using namespace std;
enum { R, D, L, U };	// 우: 0, 하: 1, 좌: 2, 상: 3
typedef struct { int x, y, d; } cctv;	// CCTV 구조체

vector<cctv> v;
int map[8][8], cpy[8][8];	// 초기 맵, 시뮬레이션을 위한 카피 맵
int N, M, ans = 2e9;

int min(int a, int b) { return a <= b ? a : b; }
// 오른쪽 감시 영역 체크
void right(int x, int y) {
	while (++y < M) {	//	오른쪽: y 증가
		if (cpy[x][y] == 6)	return;	// 벽인 경우 종료
		if (cpy[x][y] == 0)	cpy[x][y] = -1;	// 빈 공간인 경우 체크
	}
}
// 아래쪽 감시 영역 체크
void down(int x, int y) {
	while (++x < N) {	// 아래쪽: x 증가
		if (cpy[x][y] == 6)	return;	// 벽인 경우 종료
		if (cpy[x][y] == 0)	cpy[x][y] = -1;	// 빈 공간인 경우 체크
	}
}
// 왼쪽 감시 영역 체크
void left(int x, int y) {
	while (0 <= --y) {	// 왼쪽: y 감소
		if (cpy[x][y] == 6)	return;	// 벽인 경우 종료
		if (cpy[x][y] == 0)	cpy[x][y] = -1;	// 빈 공간인 경우 체크
	}
}
// 위쪽 감시 영역 체크
void up(int x, int y) {
	while (0 <= --x) {	// 위쪽: x 감소
		if (cpy[x][y] == 6)	return;	// 벽인 경우 종료
		if (cpy[x][y] == 0)	cpy[x][y] = -1;	// 빈 공간인 경우 체크
	}
}
// CCTV 종류 별 감시 영역 체크
void check(cctv c) {
	switch (cpy[c.x][c.y]) {	// CCTV 종류
	case 1:	// 1번: 한 방향
		switch (c.d) {
		case R: right(c.x, c.y); break;
		case D: down(c.x, c.y); break;
		case L: left(c.x, c.y); break;
		case U: up(c.x, c.y); break;
		}
		break;
	case 2:	// 2번: 서로 반대 두 방향
		switch (c.d) {
		case R: case L: right(c.x, c.y); left(c.x, c.y); break;	// ─
		case D: case U: down(c.x, c.y); up(c.x, c.y); break;	// │
		}
		break;
	case 3:	// 3번: 직각 두 방향
		switch (c.d) {
		case R: up(c.x, c.y); right(c.x, c.y); break;	// └
		case D: right(c.x, c.y); down(c.x, c.y); break;	// ┌
		case L: down(c.x, c.y); left(c.x, c.y); break;	// ┐
		case U: left(c.x, c.y); up(c.x, c.y); break;	// ┘
		}
		break;
	case 4:	// 4번: 세 방향
		switch (c.d) {
		case R: up(c.x, c.y); right(c.x, c.y); down(c.x, c.y); break;	// ├
		case D: right(c.x, c.y); down(c.x, c.y); left(c.x, c.y); break;	// ┬
		case L: down(c.x, c.y); left(c.x, c.y); up(c.x, c.y); break;	// ┤
		case U: left(c.x, c.y); up(c.x, c.y); right(c.x, c.y); break;	// ┴
		}
		break;
	case 5:	// 5번: 네 방향
		right(c.x, c.y); down(c.x, c.y); left(c.x, c.y); up(c.x, c.y);	// ┼
		break;
	}
}
// 정해진 방향에 대해 모든 CCTV의 감시 영역 체크
int simulation(void) {
	int ret = 0;
	// 맵 카피
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cpy[i][j] = map[i][j];
	// CCTV의 감시 영역 체크
	for (cctv c : v)
		check(c);
	// 사각 지대 크기 계산
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (!cpy[i][j])
				ret++;
	return ret;
}
// CCTV 방향의 모든 조합 탐색을 위한 dfs
void go(int n) {
	if (n == v.size()) {	// 모든 CCTV의 방향이 정해진 경우
		ans = min(ans, simulation());	// 시뮬레이션을 통한 사각 지대 크기 계산
		return;
	}
	// n번째 CCTV의 방향 지정
	for (int d = 0; d < 4; d++) {
		v[n].d = d;
		go(n + 1);
	}
}

int main(void) {
	// 입력부
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
			if (1 <= map[i][j] && map[i][j] <= 5)
				v.push_back({ i, j, 0 });
		}
	// 처리부
	go(0);
	// 출력부
	printf("%d\n", ans);
	return 0;
}
