/*
https://www.acmicpc.net/problem/3055
*/

#include <cstdio>
#include <queue>
using namespace std;
typedef struct { int x, y; } point;

queue<point> S, W;	// S: 고슴도치, W: 물
point D;	// 비버 굴
char map[50][50];
bool visited[50][50];	// 고슴도치 이동 경로 표시
int dx[4] = { 0, 0, 1, -1 };	// 동, 서, 남, 북
int dy[4] = { 1, -1, 0, 0 };	// 동, 서, 남, 북
int R, C, ans = 0;
// 물 확장
void flood(void) {
	int size = W.size();
	while (size--) {	// 세대(generation) 단위 수행. 현재 세대 물만 확장
		point now = W.front();
		W.pop();
		for (int d = 0; d < 4; d++) {
			int nx = now.x + dx[d], ny = now.y + dy[d];
			if (0 <= nx && nx < R && 0 <= ny && ny < C) {
				if (map[nx][ny] == '.') {	// 물은 돌과 비버 굴의 위치로 확장 불가
					W.push({ nx, ny });	// 다음 세대 push. 현재 작업에 포함되지 않음
					map[nx][ny] = '*';	// 물이 확장된 지역 표시
				}
			}
		}
	}
}
// 고슴도치의 이동 가능 경로 모두 탐색
void run(void) {
	int size = S.size();
	while (size--) {	// 세대(generation) 단위 수행. 현재 세대 고슴도치만 이동
		point now = S.front();
		S.pop();
		for (int d = 0; d < 4; d++) {
			int nx = now.x + dx[d], ny = now.y + dy[d];
			if (0 <= nx && nx < R && 0 <= ny && ny < C) {
				if (visited[nx][ny])	continue;	// 이미 지나온 경로로 되돌아가지 않음
				if (map[nx][ny] == '.' || map[nx][ny] == 'D') {	// 고슴도치는 돌과 물의 위치로 이동 불가
					S.push({ nx, ny });	// 다음 세대 push. 현재 작업에 포함되지 않음
					visited[nx][ny] = true;	// 고슴도치의 이동 경로 표시
				}
			}
		}
	}
}

int main(void) {
	// 입력부
	scanf("%d %d", &R, &C);
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			scanf(" %c", &map[i][j]);
			if (map[i][j] == 'S') {	// 고슴도치
				S.push({ i, j });
				visited[i][j] = true;
			}
			else if (map[i][j] == 'D')
				D = { i, j };
			else if (map[i][j] == '*')	// 물
				W.push({ i, j });
		}
	}
	// 처리부
	while (!S.empty()) {
		flood(); run();	// 물 확장 후 고슴도치 이동
		ans++;	// 소요 시간 증가
		if (visited[D.x][D.y])	// 고슴도치가 비버 굴에 도착
			break;	// 탐색 종료
	}
	// 출력부
	visited[D.x][D.y] ? printf("%d\n", ans) : printf("KAKTUS\n");
	return 0;
}