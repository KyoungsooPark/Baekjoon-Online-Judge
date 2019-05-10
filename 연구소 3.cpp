/*
https://www.acmicpc.net/problem/17142
*/

#include <cstdio>
#include <vector>
#include <queue>
#define INF	0x1FFFFFFF
using namespace std;
struct point { int x, y; };

vector<point> v;
int map[50][50], cpy[50][50];
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int N, M, empty_space = 0, ans = INF;

int min(int a, int b) { return a < b ? a : b; }

int simulation(int selected) {
	queue<point> q;
	int ret = 0, remain = empty_space;
	bool empty_space = false;
	// 시뮬레이션을 위한 맵 카피
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cpy[i][j] = map[i][j];

	// 선택된 바이러스를 큐에 삽입
	for (int i = 0; i < v.size(); i++) {
		if (selected & (1 << i)) {
			q.push(v[i]);
			cpy[v[i].x][v[i].y] = 1;
		}
	}
	// 바이러스 확산
	while (!q.empty()) {
		int size = q.size();
		ret++;
		while (size--) {
			point p = q.front(); q.pop();
			for (int d = 0; d < 4; d++) {
				int nx = p.x + dx[d], ny = p.y + dy[d];
				// 다음 위치가 벽이 아니고 방문하지 않은 곳인 경우
				if (0 <= nx && nx < N && 0 <= ny && ny < N && cpy[nx][ny] != 1) {
					if (!cpy[nx][ny] && !--remain)	// 마지막 빈 칸인 경우
						return ret;	// 해당 칸 뒤에 비활성 바이러스가 있더라도 종료
					q.push({ nx, ny });
					cpy[nx][ny] = 1;
				}
			}
		}
	}
	return remain ? INF : ret;	// 빈 칸이 남은 경우 INF, 모두 채운 경우 걸린 시간 반환
}

int main(void) {
	// 입력부
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
			switch (map[i][j]) {
			case 0: empty_space++; break;
			case 2: v.push_back({ i, j });
			}
		}
	// 처리부
	if (!empty_space) {	// 빈 칸이 없으면 0 출력 후 종료
		printf("0\n");
		return 0;
	}
	for (int i = 0; i < (1 << v.size()); i++) {
		int cnt = 0;
		for (int j = 0; j < v.size(); j++)
			if (i & (1 << j))
				cnt++;
		if (cnt == M)
			ans = min(ans, simulation(i));
	}
	// 출력부
	printf("%d\n", ans == INF ? -1 : ans);
	return 0;
}