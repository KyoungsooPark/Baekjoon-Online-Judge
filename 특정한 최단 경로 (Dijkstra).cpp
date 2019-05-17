/*
https://www.acmicpc.net/problem/1504
*/

#include <cstdio>
#include <vector>
#include <queue>
#include <functional>
#define INF	0x7FFFFFFF
using namespace std;

class Edge {
public:
	int to, cost;
	Edge(int to, int cost) { this->to = to, this->cost = cost; }
	bool operator > (const Edge &e) const { return this->cost > e.cost; }
};

vector<Edge> v[801];
int dist[801][801];
int N, E;

int min(int a, int b) { return a < b ? a : b; }

int dijkstra(int from, int to) {
	if (dist[from][to] == INF) {
		priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
		for (const Edge &e : v[from])
			pq.push(e);
		while (!pq.empty()) {
			Edge e = pq.top(); pq.pop();
			if (dist[from][e.to] >= e.cost) {
				dist[from][e.to] = dist[e.to][from] = e.cost;
				if (e.to != to)
					for (const Edge &ee : v[e.to])
						pq.push(Edge(ee.to, e.cost + ee.cost));
			}
		}
	}
	return dist[from][to];
}

int main(void) {
	int ans = -1, dst1, dst2, temp[3];
	scanf("%d %d", &N, &E);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			if (i != j)
				dist[i][j] = INF;
	while (E--) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		v[a].push_back(Edge(b, c));
		v[b].push_back(Edge(a, c));
	}
	scanf("%d %d", &dst1, &dst2);
	if (dijkstra(1, dst1) != INF && dijkstra(dst1, dst2) != INF && dijkstra(dst2, N) != INF)
		ans = dijkstra(1, dst1) + dijkstra(dst1, dst2) + dijkstra(dst2, N);
	if (dijkstra(1, dst2) != INF && dijkstra(dst1, dst2) != INF && dijkstra(dst1, N) != INF) {
		if (ans == -1)
			ans = dijkstra(1, dst2) + dijkstra(dst2, dst1) + dijkstra(dst1, N);
		else
			ans = min(ans, dijkstra(1, dst2) + dijkstra(dst2, dst1) + dijkstra(dst1, N));
	}
	printf("%d\n", ans);
	return 0;
}