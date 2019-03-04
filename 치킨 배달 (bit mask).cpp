/*
https://www.acmicpc.net/problem/15686
*/

#include <cstdio>
#include <vector>
using namespace std;
typedef struct { int x, y; } point;

vector<point> house, chicken, selected;
int map[50][50];
int N, M, ans = 2e9;

int min(int a, int b) { return a <= b ? a : b; }
int abs(int num) { return num >= 0 ? num : -num; }
int distance(point a, point b) { return abs(a.x - b.x) + abs(a.y - b.y); }

void calculate(void) {	// 선택한 M개 치킨집의 치킨 거리 계산
	int sum = 0;
	for (point h : house) {
		int temp = 2e9;
		for (point c : selected)
			temp = min(temp, distance(h, c));
		sum += temp;
	}
	ans = min(ans, sum);
}

int main(void) {
	// 입력부
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 1)
				house.push_back({ i, j });
			else if (map[i][j] == 2)
				chicken.push_back({ i, j });
		}
	// 처리부
	for (int i = 0; i < (1 << chicken.size()); i++) {
		// i: 전체 치킨집 집합에서 부분집합을 고르는 조합
		// e.g.) i = 11 = 1011(2) <- 0, 1, 3번째 치킨집 선택 (2^0, 2^1, 2^3번째 bit가 1이므로)
		// e.g.) 치킨집 수가 총 7개이고 i = (1 << 7) - 1 이면,
		//       (1 << 7) - 1 = 10000000(2) - 1 = 01111111(2) <- 0 ~ 6번째(7개) 치킨집 선택
		for (int j = 0; j < chicken.size(); j++) {
			// j: 조합(= i)에 포함된 치킨집의 인덱스 탐색
			if (i & (1 << j))
				selected.push_back(chicken[j]);
		}
		// M개의 치킨집이 선택된 경우 치킨 거리 계산
		if (selected.size() == M)
			calculate();
		selected.clear();
	}
	// 출력부
	printf("%d\n", ans);
	return 0;
}