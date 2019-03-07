/*
https://www.acmicpc.net/problem/3055
*/

#include <cstdio>
#include <queue>
using namespace std;
typedef struct { int x, y; } point;

queue<point> S, W;	// S: ����ġ, W: ��
point D;	// ��� ��
char map[50][50];
bool visited[50][50];	// ����ġ �̵� ��� ǥ��
int dx[4] = { 0, 0, 1, -1 };	// ��, ��, ��, ��
int dy[4] = { 1, -1, 0, 0 };	// ��, ��, ��, ��
int R, C, ans = 0;
// �� Ȯ��
void flood(void) {
	int size = W.size();
	while (size--) {	// ����(generation) ���� ����. ���� ���� ���� Ȯ��
		point now = W.front();
		W.pop();
		for (int d = 0; d < 4; d++) {
			int nx = now.x + dx[d], ny = now.y + dy[d];
			if (0 <= nx && nx < R && 0 <= ny && ny < C) {
				if (map[nx][ny] == '.') {	// ���� ���� ��� ���� ��ġ�� Ȯ�� �Ұ�
					W.push({ nx, ny });	// ���� ���� push. ���� �۾��� ���Ե��� ����
					map[nx][ny] = '*';	// ���� Ȯ��� ���� ǥ��
				}
			}
		}
	}
}
// ����ġ�� �̵� ���� ��� ��� Ž��
void run(void) {
	int size = S.size();
	while (size--) {	// ����(generation) ���� ����. ���� ���� ����ġ�� �̵�
		point now = S.front();
		S.pop();
		for (int d = 0; d < 4; d++) {
			int nx = now.x + dx[d], ny = now.y + dy[d];
			if (0 <= nx && nx < R && 0 <= ny && ny < C) {
				if (visited[nx][ny])	continue;	// �̹� ������ ��η� �ǵ��ư��� ����
				if (map[nx][ny] == '.' || map[nx][ny] == 'D') {	// ����ġ�� ���� ���� ��ġ�� �̵� �Ұ�
					S.push({ nx, ny });	// ���� ���� push. ���� �۾��� ���Ե��� ����
					visited[nx][ny] = true;	// ����ġ�� �̵� ��� ǥ��
				}
			}
		}
	}
}

int main(void) {
	// �Էº�
	scanf("%d %d", &R, &C);
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			scanf(" %c", &map[i][j]);
			if (map[i][j] == 'S') {	// ����ġ
				S.push({ i, j });
				visited[i][j] = true;
			}
			else if (map[i][j] == 'D')
				D = { i, j };
			else if (map[i][j] == '*')	// ��
				W.push({ i, j });
		}
	}
	// ó����
	while (!S.empty()) {
		flood(); run();	// �� Ȯ�� �� ����ġ �̵�
		ans++;	// �ҿ� �ð� ����
		if (visited[D.x][D.y])	// ����ġ�� ��� ���� ����
			break;	// Ž�� ����
	}
	// ��º�
	visited[D.x][D.y] ? printf("%d\n", ans) : printf("KAKTUS\n");
	return 0;
}