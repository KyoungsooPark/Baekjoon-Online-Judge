#include <cstdio>
using namespace std;

bool table[101][101];

int main(void) {
	int N, M, cnt = 0;
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++)
		table[i][i] = true;
	while (M--) {
		int a, b;
		scanf("%d %d", &a, &b);
		table[a][b] = table[b][a] = true;
	}
	for (int k = 1; k <= N; k++)
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				if (table[i][k] && table[k][j])
					table[i][j] = true;
	for (int i = 2; i <= N; i++)
		if (table[1][i])
			cnt++;
	printf("%d\n", cnt);
	return 0;
}