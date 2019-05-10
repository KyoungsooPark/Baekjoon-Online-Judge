/*
https://www.acmicpc.net/problem/17144
*/

#include <cstdio>
#include <vector>
using namespace std;
struct point { int x, y; };

vector<point> v;
int A[50][50], cpy[50][50];
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int R, C, T;
// 총 미세먼지량 계산
int total(void) {
	int ret = 0;
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			if (A[i][j] > 0)
				ret += A[i][j];
	return ret;
}
// 미세먼지 확산
void defuse(void) {
	// 일괄 적용을 위한 맵 카피
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			cpy[i][j] = A[i][j];
	// 미세먼지 확산
	for (int x = 0; x < R; x++)
		for (int y = 0; y < C; y++)
			if (int sub = A[x][y] / 5) {	// 미세먼지 확산이 가능한 경우
				for (int d = 0; d < 4; d++) {
					int nx = x + dx[d], ny = y + dy[d];
					if (0 <= nx && nx < R && 0 <= ny && ny < C && A[nx][ny] != -1)
						cpy[nx][ny] += sub, cpy[x][y] -= sub;
				}
			}
	// 카피맵을 이용한 일괄 업데이트
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			A[i][j] = cpy[i][j], cpy[i][j] = 0;
}
// 공기 청정
void clean(void) {
	int x = v[0].x - 1, y = v[0].y;
	// 위쪽 공기청정기의 반시계방향 순환
	while (x) { A[x][y] = A[x - 1][y], x--; }
	while (y < C - 1) { A[x][y] = A[x][y + 1], y++; }
	while (x < v[0].x) { A[x][y] = A[x + 1][y], x++; }
	while (y > 1) { A[x][y] = A[x][y - 1], y--; }
	A[x][y] = 0;	// 공기청정기에 인접한 공간
	// 아래쪽 공기청정기의 시계방향 순환
	x = v[1].x + 1, y = v[1].y;
	while (x < R - 1) { A[x][y] = A[x + 1][y], x++; }
	while (y < C - 1) { A[x][y] = A[x][y + 1], y++; }
	while (x > v[1].x) { A[x][y] = A[x - 1][y], x--; }
	while (y > 1) { A[x][y] = A[x][y - 1], y--; }
	A[x][y] = 0;	// 공기청정기에 인접한 공간
}

int main(void) {
	// 입력부
	scanf("%d %d %d", &R, &C, &T);
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++) {
			scanf("%d", &A[i][j]);
			if (A[i][j] == -1)	v.push_back({ i, j });
		}
	// 처리부
	while (T--) {
		defuse();
		clean();
	}
	// 출력부
	printf("%d\n", total());
	return 0;
}