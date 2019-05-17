/*
https://www.acmicpc.net/problem/1865
*/

#include <cstdio>
#include <vector>
#define INF	1e8
using namespace std;
struct Edge { int to, cost; };

vector<Edge> v[501];
int dist[501];
int N, M, W;

bool bellman_ford(bool check) {
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			for (const Edge& e : v[j]) {
				if (dist[j] != INF && dist[e.to] > dist[j] + e.cost) {
					if (check)	return true;
					dist[e.to] = dist[j] + e.cost;
				}
			}
	return false;
}

int main(void) {
	int TC;
	scanf("%d", &TC);
	while (TC--) {
		scanf("%d %d %d", &N, &M, &W);
		for (int i = 2; i <= N; i++)
			dist[i] = INF;
		while (M--) {
			int from, to, cost;
			scanf("%d %d %d", &from, &to, &cost);
			v[from].push_back({ to, cost });
			v[to].push_back({ from, cost });
		}
		while (W--) {
			int from, to, cost;
			scanf("%d %d %d", &from, &to, &cost);
			v[from].push_back({ to, -cost });
		}
		bellman_ford(false);
		bellman_ford(true) ? printf("YES\n") : printf("NO\n");
		for (int i = 1; i <= N; i++)
			v[i].clear();
	}
	return 0;
}