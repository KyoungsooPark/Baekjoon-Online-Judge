/*
https://www.acmicpc.net/problem/1719
*/

#include <cstdio>
using namespace std;

int dist[201][201], table[201][201];
int n, m;

int main(void) {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			dist[i][j] = (i == j ? 0 : 1e9), table[i][j] = j;
	while (m--) {
		int from, to, cost;
		scanf("%d %d %d", &from, &to, &cost);
		dist[from][to] = dist[to][from] = cost;
	}
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					table[i][j] = table[i][k];
				}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			i == j ? printf("- ") : printf("%d ", table[i][j]);
		printf("\n");
	}
	return 0;
}