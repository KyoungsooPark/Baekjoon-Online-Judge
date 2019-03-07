/*
https://www.acmicpc.net/problem/15685
*/

#include <cstdio>
#include <vector>
using namespace std;

bool map[101][101];
int dx[4] = { 0, -1, 0, 1 };	// →, ↑, ←, ↓
int dy[4] = { 1, 0, -1, 0 };	// →, ↑, ←, ↓
int N, ans = 0;

void dragon_curve(int x, int y, int d, int g) {
	// 드래곤 커브 방향 완성
	vector<int> v;	// 드래곤 커브 방향 정보 벡터
	v.push_back(d);	// 0세대 드래곤 커브 방향
	for (int i = 1; i <= g; i++)	// i: 1 ~ g세대
		for (int j = v.size() - 1; j >= 0; j--)	// j: 벡터의 역순 인덱스
			v.push_back((v[j] + 1) % 4);	// i세대 방향은 0 ~ (i - 1)세대 방향의 역순에 +1
	// 드래곤 커브 표시
	map[x][y] = true;
	for (int d : v) {
		x += dx[d], y += dy[d];
		if (0 <= x && x <= 100 && 0 <= y && y <= 100)	// 유효 좌표: 0 <= x, y <= 100
			map[x][y] = true;
	}
}

int main(void) {
	// 입력부
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		int x, y, d, g;
		scanf("%d %d %d %d", &y, &x, &d, &g);
		dragon_curve(x, y, d, g);
	}
	// 처리부
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			// 네 꼭짓점이 모두 드래곤 커브의 일부인 1 x 1 정사각형 개수 카운트
			if (map[i][j] && map[i][j + 1] && map[i + 1][j] && map[i + 1][j + 1])
				ans++;
	// 출력부
	printf("%d\n", ans);
	return 0;
}