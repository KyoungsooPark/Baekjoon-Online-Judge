/*
https://www.acmicpc.net/problem/1238
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
	Edge(int to, int cost) { this->to = to, this->cost = cost; };
	bool operator > (const Edge &e) const { return this->cost > e.cost; }
};

vector<Edge> v[1001];
vector<int> dist[1001];
int N, M, X;

int max(int a, int b) { return a > b ? a : b; }

void dijkstra(int from) {
	priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
	for (const Edge &e : v[from])
		pq.push(e);
	dist[from].assign(N + 1, INF);
	dist[from][from] = 0;
	while (!pq.empty()) {
		Edge e = pq.top(); pq.pop();
		if (dist[from][e.to] > e.cost) {
			dist[from][e.to] = e.cost;
			for (const Edge &ee : v[e.to])
				pq.push(Edge(ee.to, e.cost + ee.cost));
		}
	}
}

void dijkstra(int from, int to) {
	priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
	for (const Edge &e : v[from])
		pq.push(e);
	dist[from].assign(N + 1, INF);
	dist[from][from] = 0;
	while (!pq.empty()) {
		Edge e = pq.top(); pq.pop();
		if (dist[from][e.to] > e.cost) {
			dist[from][e.to] = e.cost;
			if (e.to != to)
				for (const Edge &ee : v[e.to])
					pq.push(Edge(ee.to, e.cost + ee.cost));
		}
	}
}

int main(void) {
	int ans = 0;
	scanf("%d %d %d", &N, &M, &X);
	while (M--) {
		int from, to, cost;
		scanf("%d %d %d", &from, &to, &cost);
		v[from].push_back(Edge(to, cost));
	}
	dijkstra(X);
	for (int i = 1; i <= N; i++) {
		dijkstra(i, X);
		ans = max(ans, dist[i][X] + dist[X][i]);
	}
	printf("%d\n", ans);
	return 0;
}