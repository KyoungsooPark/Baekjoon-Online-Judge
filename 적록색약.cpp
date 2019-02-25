/*
https://www.acmicpc.net/problem/10026
*/

#include <cstdio>
using namespace std;

char map[100][100];
bool check[100][100];
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int N;

void go1(int x, int y) {
	check[x][y] = true;
	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d], ny = y + dy[d];
		if (0 <= nx && nx < N && 0 <= ny && ny < N && !check[nx][ny])
			if (map[x][y] == map[nx][ny])	// 현재 칸과 인접 칸의 색이 같은 경우
				go1(nx, ny);
	}
}

void go2(int x, int y) {
	check[x][y] = false;
	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d], ny = y + dy[d];
		if (0 <= nx && nx < N && 0 <= ny && ny < N && check[nx][ny]) {
			if (map[x][y] == 'B' && map[nx][ny] == 'B') // 현재 칸과 인접 칸의 색이 파랑
				go2(nx, ny);
			else if (map[x][y] != 'B' && map[nx][ny] != 'B') // 현재 칸과 인접 칸의 색이 빨강 또는 초록
				go2(nx, ny);
		}
	}
}

int main(void) {
	int a = 0, b = 0;

	// 입력부
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%s", &map[i]);

	// 처리부
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (check[i][j])	continue;
			go1(i, j);
			a++;
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!check[i][j])	continue;
			go2(i, j);
			b++;
		}
	}

	// 출력부
	printf("%d %d\n", a, b);
	return 0;
}