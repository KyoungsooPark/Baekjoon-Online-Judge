/*
https://www.acmicpc.net/problem/14502
*/

#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
typedef struct { int x, y; } point;

vector<point> virus;	// 초기 바이러스 위치 저장
int map[8][8], cpy[8][8];	// 초기 맵, 시뮬레이션을 위한 카피 맵
int dx[4] = { 0, 0, 1, -1 };	// 동, 서, 남, 북
int dy[4] = { 1, -1, 0, 0 };	// 동, 서, 남, 북
int N, M, ans = 0;

int simulation(void) {
	int ret = 0;
	queue<point> q;	// 바이러스 증식을 위한 큐
	// 맵 카피
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cpy[i][j] = map[i][j];
	// 바이러스 초기 위치를 큐에 삽입
	for (point v : virus)
		q.push(v);
	// 바이러스 증식
	while (!q.empty()) {
		point now = q.front();
		q.pop();
		for (int d = 0; d < 4; d++) {
			int nx = now.x + dx[d], ny = now.y + dy[d];	// 바이러스의 증식 위치 계산
			if (0 <= nx && nx < N && 0 <= ny && ny < M) {	// 계산 위치가 맵을 벗어나지 않을 때
				if (!cpy[nx][ny]) {	// 바이러스 증식 가능 위치인 경우
					cpy[nx][ny] = 2;	// 바이러스 증식
					q.push({ nx, ny });	// 증식한 바이러스 위치를 큐에 삽입
				}
			}
		}
	}
	// 안전 영역 계산
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (!cpy[i][j])	// 안전 영역인 경우
				ret++;	// 개수 증가
	return ret;
}

void go(int x, int y, int n) {
	if (n == 3) {	// 3개의 벽을 모두 설치한 경우
		ans = max(ans, simulation());	// 최대 안전 영역 계산
		return;
	}

	for (int i = x; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (i == x && j <= y)
				continue;
			if (!map[i][j]) {	// 벽 설치 가능 위치인 경우
				map[i][j] = 1;	// 벽 설치
				go(i, j, n + 1);
				map[i][j] = 0;	// 벽 해제
			}
		}
	}
}

int main(void) {
	// 입력부
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 2)	// 바이러스인 경우
				virus.push_back({ i, j });	// 해당 위치 저장
		}
	}
	// 처리부
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (!map[i][j]) {	// 벽 설치 가능 위치인 경우
				map[i][j] = 1;	// 벽 설치
				go(i, j, 1);
				map[i][j] = 0;	// 벽 해제
			}
		}
	}
	// 출력부
	printf("%d\n", ans);
	return 0;
}
