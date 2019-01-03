/*
https://www.acmicpc.net/problem/14502
*/

#include <cstdio>
#include <queue>
using namespace std;
typedef struct { int x, y; } point;

vector<point> virus;
int map[8][8];
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int N, M, ans;

int max(int a, int b) { return a >= b ? a : b; }

int simulate(void) {
	int cpy[8][8], ret = 0;
	queue<point> q;
	// map 복사
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cpy[i][j] = map[i][j];
	// 바이러스 초기 위치 q에 삽입
	for (const point &p : virus)
		q.push(p);

	while (!q.empty()) {
		point p = q.front();
		q.pop();
		for (int d = 0; d < 4; d++) {
			int nx = p.x + dx[d], ny = p.y + dy[d];
			if (0 <= nx && nx < N && 0 <= ny && ny < M) {
				if (cpy[nx][ny] == 0) {
					cpy[nx][ny] = 2;	// 바이러스 증식
					q.push({ nx, ny });
				}
			}
		}
	}
	// 안전 영역 계산
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (cpy[i][j] == 0)
				ret++;
	return ret;
}

void go(int x, int y, int n) {
	map[x][y] = 1;	// 벽 설치

	if (n == 3) {	// 3개의 벽을 모두 설치한 경우
		ans = max(ans, simulate());	// 최대 안전 영역 계산 후
		map[x][y] = 0;	// 벽 제거
		return;
	}

	for (int i = x; i < N; i++)
		for (int j = i == x ? y + 1 : 0; j < M; j++)
			if (map[i][j] == 0)	// 벽 설치 가능 위치인 경우
				go(i, j, n + 1);	// 재귀함수 호출
	map[x][y] = 0;	// 벽 제거
}

int main(void) {
	// 입력부
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 2)
				virus.push_back({ i, j });
		}
	// 처리부
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (map[i][j] == 0)
				go(i, j, 1);
	// 출력부
	printf("%d\n", ans);
	return 0;
}
