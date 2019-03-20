/*
https://www.acmicpc.net/problem/16234
*/

#include <cstdio>
#include <queue>
#include <vector>
using namespace std;
typedef struct { int x, y; } point;

vector<point> v;
bool flag;	// 인구 이동 여부
bool check[50][50];
int map[50][50];
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int N, L, R, ans = 0;

int abs(int num) { return num >= 0 ? num : -num; }

void go(int x, int y, int &sum, int &n) {
	check[x][y] = true;		// 방문 체크
	sum += map[x][y], n++;	// 연합의 인구 수, 나라 수 업데이트
	v.push_back({ x, y });	// 연합한 나라의 위치 저장

	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d], ny = y + dy[d];
		if (0 <= nx && nx < N && 0 <= ny && ny < N && !check[nx][ny]) {
			int temp = abs(map[x][y] - map[nx][ny]);	// 인구 차이 계산
			if (L <= temp && temp <= R) {				// 인구 이동 가능
				flag = true;
				go(nx, ny, sum, n);
			}
		}
	}
}

int main(void) {
	// 입력부
	scanf("%d %d %d", &N, &L, &R);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &map[i][j]);
	// 처리부
	do {
		flag = false;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (!check[i][j]) {
					int sum = 0,	// 연합의 인구 수
						n = 0,		// 연합의 나라 수
						mean;		// 평균
					go(i, j, sum, n);	// 이동 가능 나라 조사
					mean = sum / n;
					// 연합한 나라의 인구 이동
					for (point p : v)
						map[p.x][p.y] = mean;
					v.clear();
				}
			}
		}

		if (flag) {	// 인구 이동한 경우 횟수 증가 및 check 초기화
			ans++;
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					check[i][j] = false;
		}
	} while (flag);
	// 출력부
	printf("%d\n", ans);
	return 0;
}