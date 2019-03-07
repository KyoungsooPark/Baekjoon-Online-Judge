/*
https://www.acmicpc.net/problem/16236
*/

#include <cstdio>
#include <queue>
using namespace std;
typedef struct { int x, y, dist; } point;
typedef struct { int x, y, size, cnt; } shark;

shark baby_shark;
int map[20][20];
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int N, ans = 0;

// 먹을 수 있는 물고기 존재 여부 반환
bool eatable(int x, int y) { return 0 < map[x][x] && map[x][x] < baby_shark.size; }
// 이동 가능 여부 반환
bool passable(int x, int y) { return map[x][x] == 0 || map[x][x] == baby_shark.size; }

// bfs를 이용한 물고기 탐색
point search(void) {
	int dist[20][20] = { 0 };	// "먹을 수 있는" 물고기의 거리 정보. 0으로 초기화
	point ret = { -1, -1, 400 };	// 탐색 결과 반환을 위한 변수
	queue<point> q;
	q.push({ baby_shark.x, baby_shark.y, 0 });	// 상어의 현재 위치, 거리 정보 push
	dist[baby_shark.x][baby_shark.y] = -1;	// 현재 위치 탐색 표시
	
	while (!q.empty()) {	// 현재 상어 위치로부터 전체 맵 탐색
		point now = q.front(); q.pop();
		int ndist = now.dist + 1;	// 다음 이동할 위치의 거리
		for (int d = 0; d < 4; d++) {
			int nx = now.x + dx[d], ny = now.y + dy[d];
			if (0 <= nx && nx < N && 0 <= ny && ny < N && !dist[nx][ny]) {	// 탐색하지 않은 위치
				// dist 배열 업데이트
				if (eatable(nx, ny))	// 먹을 수 있는 물고기 존재
					dist[nx][ny] = ndist;	// 거리 저장
				else	// 빈 공간 또는 먹을 수 없는 물고기가 존재
					dist[nx][ny] = -1;	// 탐색 표시
				// 이동 가능 위치로 이동
				if (passable(nx, ny))	// 이동 가능 위치
					q.push({ nx, ny, ndist });	// 큐에 삽입
			}
		}
	}
	// 왼쪽 위부터 거리가 가장 짧은 물고기 탐색
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (0 < dist[i][j] && dist[i][j] < ret.dist)
					ret = { i, j, dist[i][j] };
	return ret;
}

bool move(void) {
	point p = search();	// 먹을 물고기 위치 탐색
	if (p.x == -1)	return false;	// 더이상 먹을 수 있는 물고기가 존재하지 않는 경우 false 반환
	map[baby_shark.x][baby_shark.y] = 0, map[p.x][p.y] = 9, ans += p.dist;
	baby_shark.x = p.x, baby_shark.y = p.y, baby_shark.cnt++;	// 상어 위치, 먹은 물고기 수 업데이트
	if (baby_shark.cnt == baby_shark.size)	// 먹은 물고기 수가 상어 크기와 동일하면
		baby_shark.size++, baby_shark.cnt = 0;	// 크기 증가, 먹은 물고기 수 초기화
	return true;
}

int main(void) {
	// 입력부
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 9)	// 상어
				baby_shark = { i, j, 2, 0 };	// 상어 초기화
		}
	}
	// 처리부
	while (move());
	// 출력부
	printf("%d\n", ans);
	return 0;
}