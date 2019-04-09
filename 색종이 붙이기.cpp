/*
https://www.acmicpc.net/problem/17136
*/

#include <cstdio>
#include <queue>
using namespace std;
typedef struct { int x, y; } point;

vector<point> v;	// 색종이를 놓아야 하는 위치 저장
int map[10][10];
int check[6] = { 0, 5, 5, 5, 5, 5 };	// 남은 색종이 개수
int dx[3] = { 0, 1, 1 };	// →, ↓, ↘
int dy[3] = { 1, 0, 1 };	// →, ↓, ↘
int ans = 2e9;

int min(int a, int b) { return a < b ? a : b; }
// range 크기의 색종이를 map에 
void set(point p, int range, int val) {
	for (int i = p.x; i < p.x + range; i++)
		for (int j = p.y; j < p.y + range; j++)
			map[i][j] = val;
	val == 0 ? check[range]-- : check[range]++;
}
// 놓을 수 있는 색종이 최대 크기 계산
int max_range(point p) {
	bool visited[5][5] = { false };	// 현재 위치로부터 최대 5x5 크기 범위 방문 여부 검사
	int ret = 1;	// 주어진 위치 p에 놓을 수 있는 색종이 최소 크기
	queue<point> q;	// 주어진 위치 p로부터 →, ↓, ↘ 탐색
	q.push(p);
	visited[0][0] = true;

	while (!q.empty()) {
		int size = q.size();
		while (size--) {
			point now = q.front(); q.pop();
			for (int d = 0; d < 3; d++) {
				int nx = now.x + dx[d], ny = now.y + dy[d];
				if (0 <= nx && nx < 10 && 0 <= ny && ny < 10) {
					if (map[nx][ny] && !visited[nx - p.x][ny - p.y]) {
						q.push({ nx, ny });
						visited[nx - p.x][ny - p.y] = true;
					}
				}
			}
		}
		// ex) 2x2 가능한 경우 큐에 삽입되는 위치 수 = (2 * 1) + 1 = 3
		//     3x3 가능한 경우 큐에 삽입되는 위치 수 = (2 * 2) + 1 = 3
		//     => n x n : 2n - 1 = 2(n - 1) + 1 = 2(ret) + 1
		if (q.size() != ret * 2 + 1 || ret == 5)	return ret;
		ret++;
	}
}

void go(int i, int n, int total) {
	if (ans < n)	return;	// 현재까지의 best case를 넘어가는 경우 탐색 안함
	if (total == v.size()) {	// 모든 지점 탐색 완료
		ans = min(ans, n);
		return;
	}
	if (!map[v[i].x][v[i].y]) {	// 색종이가 이미 놓여진 위치인 경우
		go(i + 1, n, total);	// 다음 위치로 이동
		return;
	}
	// 사용 가능한 색종이 최대 크기부터 작은 크기까지 탐색
	for (int r = max_range(v[i]); r > 0; r--) {
		if (check[r]) {	// 해당 크기의 색종이 개수가 남아있는 경우
			set(v[i], r, 0);	// 색종이 사용
			go(i + 1, n + 1, total + r * r);	// 다음 위치 탐색
			set(v[i], r, 1);	// 색종이 회수
		}
	}
}

int main(void) {
	// 입력부
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j])	v.push_back({ i, j });
		}
	// 처리부
	if (!v.size()) {
		printf("0\n");
		return 0;
	}
	go(0, 0, 0);
	// 출력부
	printf("%d\n", ans == 2e9 ? -1 : ans);
	return 0;
}