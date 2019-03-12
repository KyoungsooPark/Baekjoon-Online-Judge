#include <cstdio>
#include <deque>
using namespace std;
enum { EMPTY, APPLE, OVER };
typedef struct { int x, y; } snake;

deque<snake> s;
char turn[10001];
int map[102][102];
int dx[4] = { 0, 1, 0, -1 };	// ��, ��, ��, ��
int dy[4] = { 1, 0, -1, 0 };	// ��, ��, ��, ��
int N, K, L, t, dir = 0;

int main(void) {
	// �Էº�
	scanf("%d", &N);
	for (int i = 0; i <= N + 1; i++)	// map �׵θ� ������ ǥ��
		map[i][0] = map[0][i] = map[N + 1][i] = map[i][N + 1] = OVER;
	scanf("%d", &K);
	for (int i = 0; i < K; i++) {	// K���� ��� ��ġ �Է�
		int x, y;
		scanf("%d %d", &x, &y);
		map[x][y] = APPLE;
	}
	scanf("%d", &L);
	for (int i = 0; i < L; i++) {	// �Ӹ� ȸ�� ���� �Է�
		int X; char C;
		scanf("%d %c", &X, &C);
		turn[X] = C;
	}
	// ó����
	map[1][1] = OVER, s.push_front({ 1, 1 });
	for (t = 1; t <= 10000; t++) {
		int nx = s[0].x + dx[dir], ny = s[0].y + dy[dir];

		if (map[nx][ny] == OVER) {	// ���� ����
			printf("%d\n", t);
			return 0;
		}
		if (map[nx][ny] == EMPTY) {	// �� ����
			snake tail = s.back(); s.pop_back();
			map[tail.x][tail.y] = EMPTY;
		}
		// �� ���� �Ǵ� ����� ��� �Ӹ� ��ġ ǥ�� �� push
		map[nx][ny] = OVER;
		s.push_front({ nx, ny });

		// ���� ���� ���� ������Ʈ
		if (turn[t] == 'L')
			dir == 0 ? dir = 3 : dir--;
		else if (turn[t] == 'D')
			dir == 3 ? dir = 0 : dir++;
	}
	return 0;
}