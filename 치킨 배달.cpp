/*
https://www.acmicpc.net/problem/15686
*/

#include <cstdio>
#include <vector>
using namespace std;
typedef struct { int x, y; } point;

vector<point> house, chicken;
bool check[13];
int map[50][50];
int N, M, ans = 2e9;

int min(int a, int b) { return a <= b ? a : b; }
int abs(int num) { return num >= 0 ? num : -num; }
int distance(point a, point b) { return abs(a.x - b.x) + abs(a.y - b.y); }

void go(int n, int l) {	// n: 탐색한 치킨집 수, l: 선택한 치킨집 수
	if (n == chicken.size()) {	// 모든 치킨집에 대해 탐색 완료
		if (l == M) {	// 선택한 치킨집의 수가 M이면 최소 치킨 거리 계산
			int sum = 0;	// 모든 집과 선택된 치킨집의 치킨 거리 누적합산 변수
			for (int i = 0; i < house.size(); i++) {
				int temp = 2e9;	// i번째 집의 최소 치킨 거리 저장 변수
				for (int j = 0; j < chicken.size(); j++)
					if (check[j])	// j번째 치킨집이 선택된 경우
						// i번째 집과 j번째 치킨집의 거리 계산
						temp = min(temp, distance(house[i], chicken[j]));
				sum += temp;
			}
			ans = min(ans, sum);
		}
		return;
	}
	check[n] = true; go(n + 1, l + 1);	// n번째 치킨집 선택
	check[n] = false; go(n + 1, l);		// n번째 치킨집 탈락
}

int main(void) {
	// 입력부
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 1) // 집
				house.push_back({ i, j });
			else if (map[i][j] == 2) // 치킨집
				chicken.push_back({ i, j });
		}
	// 처리부
	go(0, 0);
	// 출력부
	printf("%d\n", ans);
	return 0;
}
