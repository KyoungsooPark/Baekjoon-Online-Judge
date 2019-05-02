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
	for (const Edge &e : v[1])	// ù ��° ������ ����� ��� ����
		pq.push(e);	// �ּ� �� �켱���� ť�� ����
	visited[1] = true;	// ù ��° ���� �湮 üũ

	while (!pq.empty()) {	// ������� �湮�� ������ ����� ��� ���� �˻�
		Edge e = pq.top(); pq.pop();	// ����ġ�� ���� ���� ���� ����
		if (!visited[e.to]) {	// ������ ����� ������ ���� �湮���� ���� ���
			ret += e.weight;	// �ش� ���� ����
			visited[e.to] = true;	// ������ ������ ����� ���� �湮
			for (const Edge &ee : v[e.to])	// ������ ����� ��� ���� ��
				if (!visited[ee.to])	// �湮 ���� ������ ����� ����
					pq.push(ee);	// ���� Ž���� ���� �켱���� ť�� ����
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