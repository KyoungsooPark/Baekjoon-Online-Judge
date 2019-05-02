/*
https://www.acmicpc.net/problem/4485
*/

#include <cstdio>
#include <queue>
#include <functional>
using namespace std;

struct Edge {
	int x, y, c;
	bool operator > (const Edge e) const { return c > e.c; }
};

int map[125][125], dist[125][125];
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int N;

int dijkstra(void) {
	priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
	pq.push({ 0, 0, map[0][0] });
	while (!pq.empty()) {
		Edge e = pq.top(); pq.pop();
		if (dist[e.x][e.y] < e.c)	continue;
		dist[e.x][e.y] = e.c;
		for (int d = 0; d < 4; d++) {
			int nx = e.x + dx[d], ny = e.y + dy[d];
			if (0 <= nx && nx < N && 0 <= ny && ny < N) {
				int nc = e.c + map[e.x][e.y];
				if (dist[nx][ny] > nc)
					pq.push({ nx, ny, e.c + map[nx][ny] });
			}
		}
	}
	return dist[N - 1][N - 1];
}

int main(void) {
	for (int t = 1;		; t++) {
		scanf("%d", &N);
		if (!N)	break;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				scanf("%d", &map[i][j]), dist[i][j] = 0x7FFFFFFF;
		printf("Problem %d: %d\n", t, dijkstra());
	}
	return 0;
}