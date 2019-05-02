/*
https://www.acmicpc.net/problem/1197
*/

#include <cstdio>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

class Edge {
public:
	int to, weight;
	Edge(int to, int weight) { this->to = to, this->weight = weight; }
	bool operator > (const Edge &e) const { return this->weight > e.weight; }
};

vector<Edge> v[10001];
bool visited[10001];
int V, E;

int prim(void) {
	int ret = 0;
	priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
	for (const Edge &e : v[1])	// 첫 번째 정점과 연결된 모든 간선
		pq.push(e);	// 최소 힙 우선순위 큐에 삽입
	visited[1] = true;	// 첫 번째 간선 방문 체크

	while (!pq.empty()) {	// 현재까지 방문한 정점에 연결된 모든 간선 검사
		Edge e = pq.top(); pq.pop();	// 가중치가 가장 작은 간선 선택
		if (!visited[e.to]) {	// 간선과 연결된 정점을 아직 방문하지 않은 경우
			ret += e.weight;	// 해당 간선 선택
			visited[e.to] = true;	// 선택한 간선과 연결된 정점 방문
			for (const Edge &ee : v[e.to])	// 정점과 연결된 모든 간선 중
				if (!visited[ee.to])	// 방문 안한 정점과 연결된 간선
					pq.push(ee);	// 다음 탐색을 위해 우선순위 큐에 삽입
		}
	}
	return ret;
}

int main(void) {
	scanf("%d %d", &V, &E);
	while (E--) {
		int A, B, C;
		scanf("%d %d %d", &A, &B, &C);
		v[A].push_back(Edge(B, C));
		v[B].push_back(Edge(A, C));
	}
	printf("%d\n", prim());
	return 0;
}