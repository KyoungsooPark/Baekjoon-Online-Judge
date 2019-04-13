/*
https://www.acmicpc.net/problem/17136
*/

#include <iostream>
#include <vector>
using namespace std;
struct point { int x, y; };

vector<point> v;	// 색종이를 놓아야 하는 위치 저장
bool map[10][10];
int cnt[6] = { 0, 5, 5, 5, 5, 5 };	// 남은 색종이 개수
int ans = 2e9;

int min(int a, int b) { return a < b ? a : b; }
// 놓을 수 있는 색종이 최대 크기 계산
// 검사 범위 r을 증가시키며 오른쪽, 아래 테두리 검사
// ex) (x, y)에서 2x2 검사 => (x, y + 1), (x + 1, y + 1), (x, y + 1) 검사
int max_range(point p) {
	int r;
	for (r = 1; r < 5; r++) {
		for (int x = p.x; x <= p.x + r; x++)
			if (x > 9 || p.y + r > 9 || !map[x][p.y + r])
				return r;
		for (int y = p.y; y < p.y + r; y++)
			if (p.x + r > 9 || y > 9 || !map[p.x + r][y])
				return r;
	}
	return r;
}
// range 크기의 색종이를 map에 사용 또는 회수
void set(point p, int range, bool val) {
	for (int x = p.x; x < p.x + range; x++)
		for (int y = p.y; y < p.y + range; y++)
			map[x][y] = val;
	val ? cnt[range]++ : cnt[range]--;	// false인 경우 사용, true인 경우 회수
}

void go(int idx, int n, int total) {
	if (total == v.size()) {	// 모든 지점 탐색 완료
		ans = min(ans, n);
		return;
	}
	if (ans == n)	return;	// 현재까지의 best case를 넘어가는 경우 탐색 안함
	if (!map[v[idx].x][v[idx].y]) {	// 색종이가 이미 놓여진 위치인 경우
		go(idx + 1, n, total);	// 다음 위치로 이동
		return;
	}
	// 사용 가능한 색종이 최대 크기부터 작은 크기까지 탐색
	for (int r = max_range(v[idx]); r > 0; r--) {
		if (cnt[r]) {	// 해당 크기의 색종이 개수가 남아있는 경우
			set(v[idx], r, false);	// 색종이 사용
			go(idx + 1, n + 1, total + r * r);	// 다음 위치 탐색
			set(v[idx], r, true);	// 색종이 회수
		}
	}
}

int main(void) {
	// 입력부
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++) {
			cin >> map[i][j];
			if (map[i][j])
				v.push_back({ i, j });
		}
	// 처리부
	go(0, 0, 0);
	// 출력부
	printf("%d\n", ans == 2e9 ? -1 : ans);
	return 0;
}