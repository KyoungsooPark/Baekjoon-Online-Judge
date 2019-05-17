/*
https://www.acmicpc.net/problem/11657
*/

#include <cstdio>
#include <vector>
#define INF	0x3FFFFFFF
using namespace std;
struct Edge { int to, cost; };

vector<Edge> v[501];
int dist[501];
int N, M;

bool bellman_ford(bool check) {
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			for (const Edge e : v[j])
				if (dist[j] != INF && dist[e.to] > dist[j] + e.cost) {
					if (check)	return true;
					dist[e.to] = dist[j] + e.cost;
				}
	return false;
}

int main(void) {
	scanf("%d %d", &N, &M);
	while (M--) {
		int A, B, C;
		scanf("%d %d %d", &A, &B, &C);
		v[A].push_back({ B, C });
	}
	for (int i = 2; i <= N; i++)	dist[i] = INF;
	bellman_ford(false);
	if (bellman_ford(true))	printf("-1\n");
	else {
		for (int i = 2; i <= N; i++)
			printf("%d\n", dist[i] == INF ? -1 : dist[i]);
	}
	return 0;
}