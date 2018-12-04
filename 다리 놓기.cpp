/*
https://www.acmicpc.net/problem/1010
*/

#include <cstdio>
using namespace std;

int d[30][30];

int calculate(int n, int m) {
	if (n == 0 || n == m)
		return 1;
	if (d[n][m])
		return d[n][m];
	// �� ������ ù ��° ����Ʈ�� ������ ù ��° ����Ʈ�� ������ ���
	// + ������ ù ��° ����Ʈ�� �������� ���� ���
	return d[n][m] = calculate(n - 1, m - 1) + calculate(n, m - 1);
}

int main(void) {
	int T;
	scanf("%d", &T);
	while (T--) {
		int N, M, ans = 0;
		scanf("%d %d", &N, &M);
		printf("%d\n", calculate(N, M));
	}
	return 0;
}