/*

*/

#include <cstdio>
using namespace std;
enum { TOP, BOTTOM, LEFT, RIGHT, FRONT, BACK };
int map[20][20], cube[6], *ptr[6];
int dx[5] = { 0, 0, 0, -1, 1 };
int dy[5] = { 0, 1, -1, 0, 0 };
int N, M, x, y, K;

void move(int d) {
	int nx = x + dx[d], ny = y + dy[d];
	int *temp = ptr[TOP];
	if (nx < 0 || N <= nx || ny < 0 || M <= ny)	// map�� �Ѿ ���
		return;	// �ش� ��� �� ��� ����
	switch (d) {
	case 1:	// ��
		ptr[TOP] = ptr[LEFT];
		ptr[LEFT] = ptr[BOTTOM];
		ptr[BOTTOM] = ptr[RIGHT];
		ptr[RIGHT] = temp;
		break;
	case 2:	// ��
		ptr[TOP] = ptr[RIGHT];
		ptr[RIGHT] = ptr[BOTTOM];
		ptr[BOTTOM] = ptr[LEFT];
		ptr[LEFT] = temp;
		break;
	case 3:	// ��
		ptr[TOP] = ptr[FRONT];
		ptr[FRONT] = ptr[BOTTOM];
		ptr[BOTTOM] = ptr[BACK];
		ptr[BACK] = temp;
		break;
	case 4:	// ��
		ptr[TOP] = ptr[BACK];
		ptr[BACK] = ptr[BOTTOM];
		ptr[BOTTOM] = ptr[FRONT];
		ptr[FRONT] = temp;
		break;
	}
	if (map[nx][ny]) {	// �̵��� ĭ�� ���� �ִ� ���� 0�� �ƴϸ�
		*ptr[BOTTOM] = map[nx][ny];	// ĭ�� ���� �ִ� ���� �ֻ����� �ٴڸ����� ����
		map[nx][ny] = 0;	// ĭ�� ���� �ִ� ���� 0�� ��
	}
	else	// �̵��� ĭ�� ���� �ִ� ���� 0�̸�
		map[nx][ny] = *ptr[BOTTOM];	// �ֻ����� �ٴڸ鿡 ���� �ִ� ���� ĭ�� ����
	printf("%d\n", *ptr[TOP]);	// �̵��� ������ �ֻ����� �� �鿡 ���� �ִ� �� ���
	x = nx, y = ny;	// �ֻ��� ��ġ ����
}

int main(void) {
	for (int i = 0; i < 6; i++)
		ptr[i] = &cube[i];
	scanf("%d %d %d %d %d", &N, &M, &x, &y, &K);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			scanf("%d", &map[i][j]);

	while (K--) {
		int d;
		scanf("%d", &d);
		move(d);
	}
	return 0;
}