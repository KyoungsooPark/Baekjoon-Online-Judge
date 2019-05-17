/*
https://www.acmicpc.net/problem/1753
*/

#include <cstdio>
#include <vector>
#include <queue>
#include <functional>
#define INF    0x3FFFFFFF
using namespace std;
struct Edge {
	int to, cost;
	bool operator > (const Edge& e) const { return cost > e.cost; }
};

vector<Edge> v[20001];
int dist[20001];
int V, E, K;

void dijkstra(void) {
	priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
	for (const Edge& e : v[K])		pq.push(e);
	for (int i = 1; i <= V; i++)	dist[i] = INF;
	dist[K] = 0;
	while (!pq.empty()) {
		Edge e = pq.top(); pq.pop();
		if (dist[e.to] > e.cost) {
			dist[e.to] = e.cost;
			for (const Edge& ee : v[e.to])
				pq.push({ ee.to, dist[e.to] + ee.cost });
		}
	}
}

int main(void) {
	scanf("%d %d %d", &V, &E, &K);
	while (E--) {
		int from, to, cost;
		scanf("%d %d %d", &from, &to, &cost);
		v[from].push_back({ to, cost });
	}
	dijkstra();
	for (int i = 1; i <= V; i++)
		dist[i] == INF ? printf("INF\n") : printf("%d\n", dist[i]);
	return 0;
}