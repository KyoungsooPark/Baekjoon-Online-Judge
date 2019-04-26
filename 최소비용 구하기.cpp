#include <cstdio>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

class Edge {
public:
	int to, cost;
	Edge(int to, int cost) { this->to = to, this->cost = cost; }
	bool operator > (const Edge &e) const { return this->cost > e.cost; }
};

vector<Edge> v[1001];
vector<int> dist;
int N, M;

int dijkstra(int From, int To) {
	priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
	for (const Edge &e : v[From])
		pq.push(e);
	dist.assign(N + 1, 0x7FFFFFF);
	dist[From] = 0;
	while (!pq.empty()) {
		Edge e = pq.top(); pq.pop();
		if (e.cost < dist[e.to]) {
			dist[e.to] = e.cost;
			if (e.to != To) {
				for (const Edge &ee : v[e.to])
					pq.push(Edge(ee.to, e.cost + ee.cost));
			}
		}
	}
	return dist[To];
}

int main(void) {
	int From, To;
	scanf("%d %d", &N, &M);
	while (M--) {
		int from, to, cost;
		scanf("%d %d %d", &from, &to, &cost);
		v[from].push_back(Edge(to, cost));
	}
	scanf("%d %d", &From, &To);
	printf("%d\n", dijkstra(From, To));
	return 0;
}