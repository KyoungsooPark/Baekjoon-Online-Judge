/*
https://www.acmicpc.net/problem/1238
*/

#include <cstdio>
using namespace std;

int dist[1001][1001];
int N, M, X;

int max(int a, int b) { return a > b ? a : b; }

int main(void) {
	int ans = 0;
	scanf("%d %d %d", &N, &M, &X);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			dist[i][j] = (i == j ? 0 : 1e6);
	while (M--) {
		int from, to, cost;
		scanf("%d %d %d", &from, &to, &cost);
		dist[from][to] = cost;
	}
	for (int k = 1; k <= N; k++)
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				if (dist[i][j] > dist[i][k] + dist[k][j])
					dist[i][j] = dist[i][k] + dist[k][j];
	for (int i = 1; i <= N; i++)
		ans = max(ans, dist[i][X] + dist[X][i]);
	printf("%d\n", ans);
	return 0;
}