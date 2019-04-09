/*
https://www.acmicpc.net/problem/11559
*/

#include <cstdio>
using namespace std;

bool check[12][6];
char map[12][6];
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int ans = -1;

void swap(char &a, char &b) { char temp = a; a = b; b = temp; }
bool isblock(int x, int y) { return map[x][y] && map[x][y] != '.'; }
// (x, y) 위치로부터 연속된 블록 수 검사
int search(int x, int y, int n) {
	check[x][y] = true;
	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d], ny = y + dy[d];
		if (0 <= nx && nx < 12 && 0 <= ny && ny < 6 && !check[nx][ny])
			if (map[x][y] == map[nx][ny])
				n += search(nx, ny, 1);
	}
	return n;
}
// (x, y) 위치로부터 4개 이상 연속된 블록 제거
void del(int x, int y, char b) {
	map[x][y] = '.';
	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d], ny = y + dy[d];
		if (0 <= nx && nx < 12 && 0 <= ny && ny < 6 && check[nx][ny])
			if (map[nx][ny] == b)
				del(nx, ny, b);
	}
}
// 블록 드랍
void drop(void) {
	for (int y = 0; y < 6; y++) {
		for (int x = 11; x > 0; x--) {
			if (map[x][y] == '.')
				for (int xx = x - 1; xx >= 0; xx--)
					if (isblock(xx, y))
						swap(map[x--][y], map[xx][y]);
		}
	}
}
// 방문 여부 초기화
void reset_check(void) {
	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 6; j++)
			check[i][j] = false;
}

int main(void) {
	// 입력부
	for (int i = 0; i < 12; i++)
		scanf("%s", &map[i]);
	// 처리부
	bool flag;
	do {
		ans++;
		flag = false;
		for (int i = 11; i >= 0; i--) {
			for (int j = 0; j < 6; j++) {
				if (isblock(i, j) && !check[i][j] && search(i, j, 1) > 3) {
					del(i, j, map[i][j]);
					flag = true;
				}
			}
		}
		if (flag)
			drop();
		reset_check();
	} while (flag);
	// 출력부
	printf("%d\n", ans);
	return 0;
}