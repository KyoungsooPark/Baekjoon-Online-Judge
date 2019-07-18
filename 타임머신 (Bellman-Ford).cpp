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

bool edge_relaxation(bool check) {
	// 모든 노드에 대해
	for (int j = 1; j <= N; j++)
		// 해당 노드와 연결된 모든 간선
		for (const Edge e : v[j])
			// 가중치 업데이트 가능 여부 검사
			if (dist[j] != INF && dist[e.to] > dist[j] + e.cost) {
				// 음수 사이클 체크인 경우
				if (check)	return true;
				// 가중치 업데이트
				dist[e.to] = dist[j] + e.cost;
			}
	return false;
}

bool bellman_ford(void) {
	// 노드 개수만큼 edge_relaxation 수행
	for (int i = 1; i <= N; i++)
		edge_relaxation(false);
	// 다시 한번 edge_relaxation 수행하여 음수 사이클 여부 검사
	return edge_relaxation(true);
}

int main(void) {
	scanf("%d %d", &N, &M);
	while (M--) {
		int A, B, C;
		scanf("%d %d %d", &A, &B, &C);
		v[A].push_back({ B, C });
	}
	for (int i = 2; i <= N; i++)
		dist[i] = INF;
	if (bellman_ford())
		printf("-1\n");
	else
		for (int i = 2; i <= N; i++)
			printf("%d\n", dist[i] == INF ? -1 : dist[i]);
	return 0;
}
