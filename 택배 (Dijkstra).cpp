/*
https://www.acmicpc.net/problem/1719
*/

#include <cstdio>
#include <vector>
#include <queue>
#include <functional>
#define INF	0x3FFFFFFF
using namespace std;

struct Edge {
	int from, to, cost;
	bool operator > (const Edge &e) const { return cost > e.cost; }
};

vector<Edge> v[201];
int dist[201][201], table[201][201];
int n, m;

int Find(int from, int cur, int to) {
	if (table[from][cur] == cur)	return cur;
	table[table[from][cur]][to] = Find(table[from][cur], cur, to);
	return table[from][cur];
}

void dijkstra(int from) {
	priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
	for (const Edge &e : v[from])
		pq.push(e);
	for (int i = 1; i <= n; i++)
		dist[from][i] = INF;
	dist[from][from] = 0;
	while (!pq.empty()) {
		Edge e = pq.top(); pq.pop();
		if (dist[from][e.to] > e.cost) {
			dist[from][e.to] = e.cost;
			table[e.from][e.to] = e.to;
			if (e.from != from)
				table[from][e.to] = Find(from, e.from, e.to);
			for (const Edge &ee : v[e.to])
				pq.push({ e.to, ee.to, e.cost + ee.cost });
		}
	}
}

int main(void) {
	scanf("%d %d", &n, &m);
	while (m--) {
		int from, to, cost;
		scanf("%d %d %d", &from, &to, &cost);
		v[from].push_back({ from, to, cost });
		v[to].push_back({ to, from, cost });
	}
	for (int i = 1; i <= n; i++)
		dijkstra(i);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			table[i][j] ? printf("%d ", table[i][j]) : printf("- ");
		printf("\n");
	}
	return 0;
}