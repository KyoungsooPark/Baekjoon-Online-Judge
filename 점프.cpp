/*
https://www.acmicpc.net/problem/1890
*/

#include <cstdio>
using namespace std;

int map[101][101];
long long d[101][101];

int main(void) {
	int N;
	// �Էº�
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			scanf("%d", &map[i][j]);
	// ó����
	d[1][1] = 1;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			// ��ΰ� ���� ��ġ �Ǵ� �������� ���
			if (!d[i][j] || (i == N && j == N))
				continue;
			int down = i + map[i][j];
			int right = j + map[i][j];
			if (down <= N)
				d[down][j] += d[i][j];
			if (right <= N)
				d[i][right] += d[i][j];
		}
	}
	// ��º�
	printf("%lld\n", d[N][N]);
	return 0;
}