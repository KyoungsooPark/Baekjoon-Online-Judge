/*
https://www.acmicpc.net/problem/16234
*/

#include <cstdio>
#include <queue>
#include <vector>
using namespace std;
typedef struct { int x, y; } point;

bool check[50][50];
int map[50][50], next_map[50][50];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int N, L, R;

int abs(int num) { return num >= 0 ? num : -num; }

bool bfs(void) {
	bool ret = false;
	queue<point> q;
	vector<point> v;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (check[i][j])	continue;
			q.push({ i, j }), v.push_back({ i, j }), check[i][j] = true;
			while (!q.empty()) {
				point p = q.front(); q.pop();
				for (int d = 0; d < 4; d++) {
					int nx = p.x + dx[d], ny = p.y + dy[d];
					if (0 <= nx && nx < N && 0 <= ny && ny < N && !check[nx][ny]) {
						int num = abs(map[p.x][p.y] - map[nx][ny]);
						if (L <= num  && num <= R)	// 해당 국가로 인구 이동이 가능한 경우
							q.push({ nx, ny }), v.push_back({ nx, ny }), check[nx][ny] = true;
					}
				}
			}
			if (v.size() > 1) {	// 인구 이동이 가능한 국가가 존재하는 경우
				int temp = 0;
				// 인구수 평균 계산
				for (const point &p : v)
					temp += map[p.x][p.y];
				temp /= v.size();
				// 평균 인구수로 분배
				for (const point &p : v)
					next_map[p.x][p.y] = temp;
			}
			else	// 인구 이동이 가능한 국가가 존재하지 않는 경우
				check[i][j] = false;	// 해당 탐색 지점의 check 상태 초기화
			v.clear();	// 이동 가능 국가 초기화
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] != next_map[i][j]) {	// 인구 이동이 있었으면
				map[i][j] = next_map[i][j];	// 이동한 인구를 적용
				ret = true;	// 인구의 이동이 있었음을 표시
			}
			check[i][j] = false;	// 모든 check 상태 초기화
		}
	}
	return ret;
}

int main(void) {
	int ans = 0;
	// 입력부
	scanf("%d %d %d", &N, &L, &R);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &map[i][j]), next_map[i][j] = map[i][j];

	// 처리부
	while (bfs())
		ans++;

	// 출력부
	printf("%d\n", ans);
	return 0;
}