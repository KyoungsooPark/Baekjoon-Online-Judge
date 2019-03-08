/*
https://www.acmicpc.net/problem/2573
*/

#include <cstdio>
#include <queue>
using namespace std;
typedef struct { int x, y; } point;

queue<point> q;
bool check[300][300];
int map[2][300][300];
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int N, M, cur = 0, ans = 0;
// 빙산 군집 검사를 위한 dfs
void go(int x, int y) {
	check[x][y] = true;
	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d], ny = y + dy[d];
		if (map[cur][nx][ny] && !check[nx][ny]) // 방문하지 않은 빙산
			go(nx, ny);
	}
}
// 빙산의 군집 개수 반환
int cluster(void) {
	int ret = 0;
	for (int i = 1; i < N - 1; i++)
		for (int j = 1; j < M - 1; j++)
			if (map[cur][i][j] && !check[i][j]) {
				go(i, j);
				ret++;
			}
	// check 배열 초기화
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			check[i][j] = false;
	return ret;
}
// 빙산이 바다에 접한 면적 반환
int count(point p) {
	int ret = 0;
	for (int d = 0; d < 4; d++) {
		int nx = p.x + dx[d], ny = p.y + dy[d];
		if (!map[cur][nx][ny])
			ret++;
	}
	return ret;
}

int main(void) {
	// 입력부
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[cur][i][j]);
			if (map[cur][i][j])
				q.push({ i, j });	// 초기 빙산 위치 저장
		}
	}
	// 처리부
	while (!q.empty()) {
		int size = q.size();
		int next = (cur + 1) % 2;

		if (cluster() > 1) {	// 빙산이 둘 이상으로 분리된 경우
			printf("%d\n", ans); // 소요 시간 출력 후
			return 0;	// 종료
		}
		while (size--) {	// 세대(generation) 단위 수행
			point p = q.front(); q.pop();
			int cnt = count(p);	// 빙산이 녹는 양
			if (map[cur][p.x][p.y] > cnt) {	// 빙산이 다 녹지 않을 경우
				map[next][p.x][p.y] = map[cur][p.x][p.y] - cnt; // map[next]에 남은 높이 저장
				q.push(p);	// 큐에 다시 삽입
			}
		}
		// 이전 맵 초기화
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				map[cur][i][j] = 0;
		cur = next;	// cur을 갱신된 맵의 인덱스로 업데이트
		ans++;	// 시간 증가
	}

	printf("0\n");	// 모두 녹을 때까지 빙산이 분리되지 않음
	return 0;
}