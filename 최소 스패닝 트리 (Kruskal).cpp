/*
https://www.acmicpc.net/problem/1197
*/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

class Edge {
public:
	int left, right, weight;
	Edge(int left, int right, int weight) { this->left = left, this->right = right, this->weight = weight; }
	bool operator < (const Edge &e) const { return this->weight < e.weight; }
};

vector<Edge> v;
int set[10001];
int V, E;
// 정점 x의 집합 번호 반환
int Find(int x) { return set[x] == x ? x : set[x] = Find(set[x]); }
// 서로 다른 두 정점 a, b를 동일한 집합으로 구성
void Union(int a, int b) { a = Find(a), b = Find(b); a < b ? set[b] = a : set[a] = b; }
// 서로 다른 두 정점 a, b가 동일 집합인지 검사
bool isUnion(int a, int b) { return Find(a) == Find(b); }
// Kruskal 알고리즘
long long kruskal(void) {
	long long ret = 0;
	for (int v = 1; v <= V; v++)
		set[v] = v;	// 초기 모든 정점의 집합 번호를 자신의 번호로 설정
	sort(v.begin(), v.end());	// graph의 모든 간선을 가중치 기준 오름차순 정렬
	for (const Edge &e : v) {	// 정렬된 간선에 대해 순서대로 사이클 검사 및 선택
		if (!isUnion(e.left, e.right)) {	// 두 정점이 서로 다른 집합 => 간선 선택 시 사이클 발생 안함
			ret += e.weight;	// 간선 선택
			Union(e.left, e.right);	// 동일 집합으로 구성
		}
	}
	return ret;
}

int main(void) {
	scanf("%d %d", &V, &E);
	while (E--) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		v.push_back(Edge(a, b, c));
	}
	printf("%d\n", kruskal());
	return 0;
}