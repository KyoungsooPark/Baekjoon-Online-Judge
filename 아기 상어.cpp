/*
https://www.acmicpc.net/problem/16236
*/

#include <cstdio>
#include <queue>
using namespace std;
typedef struct { int x, y, z; } point;
typedef struct { int x, y, size, cnt; } shark;

shark s;
int map[20][20];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int N, ans;

// 목적지(dstx, dsty)까지의 이동거리 반환
// limit을 초과하거나 도달할 수 없으면 2e9 반환
int distance(int dstx, int dsty, int limit) {
	queue<point> q;
	bool visited[20][20] = { false, };

	visited[s.x][s.y] = true, q.push({ s.x, s.y, 0 });
	while (!q.empty()) {
		point p = q.front();
		q.pop();
		if (p.x == dstx && p.y == dsty)	// 목적지에 도달한 경우
			return p.z;	// 이동거리 반환
		if (p.z >= limit)	// limit을 초과하는 경우
			return 2e9;

		for (int d = 0; d < 4; d++) {
			int nx = p.x + dx[d], ny = p.y + dy[d];
			if (0 <= nx && nx < N && 0 <= ny && ny < N && visited[nx][ny] == false)
				if (map[nx][ny] <= s.size)
					visited[nx][ny] = true, q.push({ nx, ny, p.z + 1 });
		}
	}
	return 2e9;	// 목적지에 도달할 수 없는 경우
}

bool move(void) {
	int nx, ny, dist = 2e9;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (0 < map[i][j] && map[i][j] < s.size) {	// 다음 목적지 탐색
				int temp = distance(i, j, dist);	// 목적지까지의 이동거리
				if (dist > temp) {	// 이동거리가 가장 가까운 목적지 선정
					dist = temp;
					nx = i, ny = j;
				}
			}
		}
	}
	if (dist == 2e9)	// 가능한 목적지가 없는 경우
		return false;	// false 반환

	s.x = nx, s.y = ny;	// 목적지로 이동
	map[nx][ny] = 0;	// 해당 위치의 물고기를 먹음
	ans += dist;	// 총 이동거리 누적
	if (--s.cnt == 0) {	// 아기 상어가 자신의 크기만큼의 물고기를 먹은 경우
		s.size++;	// 크기 증가
		s.cnt = s.size;	// 다음 크기 증가까지 먹어야 할 물고기 수 갱신
	}
	return true;
}



int main(void) {
	// 입력부
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 9) {
				map[i][j] = 0;
				s = { i, j, 2, 2 };
			}
		}
	}

	// 처리부
	while (move());

	// 출력부
	printf("%d\n", ans);

	return 0;
}